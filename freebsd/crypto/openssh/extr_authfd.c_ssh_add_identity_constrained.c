#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int type; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
#define  KEY_DSA 137 
#define  KEY_DSA_CERT 136 
#define  KEY_ECDSA 135 
#define  KEY_ECDSA_CERT 134 
#define  KEY_ED25519 133 
#define  KEY_ED25519_CERT 132 
#define  KEY_RSA 131 
#define  KEY_RSA_CERT 130 
#define  KEY_XMSS 129 
#define  KEY_XMSS_CERT 128 
 int /*<<< orphan*/  SSH2_AGENTC_ADD_IDENTITY ; 
 int /*<<< orphan*/  SSH2_AGENTC_ADD_ID_CONSTRAINED ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int decode_reply (int /*<<< orphan*/ ) ; 
 int encode_constraints (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssh_request_reply (int,struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int sshbuf_get_u8 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshkey_private_serialize_maxsign (struct sshkey const*,struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ssh_add_identity_constrained(int sock, const struct sshkey *key,
    const char *comment, u_int life, u_int confirm, u_int maxsign)
{
	struct sshbuf *msg;
	int r, constrained = (life || confirm || maxsign);
	u_char type;

	if ((msg = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;

	switch (key->type) {
#ifdef WITH_OPENSSL
	case KEY_RSA:
	case KEY_RSA_CERT:
	case KEY_DSA:
	case KEY_DSA_CERT:
	case KEY_ECDSA:
	case KEY_ECDSA_CERT:
#endif
	case KEY_ED25519:
	case KEY_ED25519_CERT:
	case KEY_XMSS:
	case KEY_XMSS_CERT:
		type = constrained ?
		    SSH2_AGENTC_ADD_ID_CONSTRAINED :
		    SSH2_AGENTC_ADD_IDENTITY;
		if ((r = sshbuf_put_u8(msg, type)) != 0 ||
		    (r = sshkey_private_serialize_maxsign(key, msg, maxsign,
		    NULL)) != 0 ||
		    (r = sshbuf_put_cstring(msg, comment)) != 0)
			goto out;
		break;
	default:
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}
	if (constrained &&
	    (r = encode_constraints(msg, life, confirm, maxsign)) != 0)
		goto out;
	if ((r = ssh_request_reply(sock, msg, msg)) != 0)
		goto out;
	if ((r = sshbuf_get_u8(msg, &type)) != 0)
		goto out;
	r = decode_reply(type);
 out:
	sshbuf_free(msg);
	return r;
}