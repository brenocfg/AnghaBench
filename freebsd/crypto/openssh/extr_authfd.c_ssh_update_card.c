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
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_AGENTC_ADD_SMARTCARD_KEY ; 
 int /*<<< orphan*/  SSH_AGENTC_ADD_SMARTCARD_KEY_CONSTRAINED ; 
 int /*<<< orphan*/  SSH_AGENTC_REMOVE_SMARTCARD_KEY ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int decode_reply (int /*<<< orphan*/ ) ; 
 int encode_constraints (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssh_request_reply (int,struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int sshbuf_get_u8 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 

int
ssh_update_card(int sock, int add, const char *reader_id, const char *pin,
    u_int life, u_int confirm)
{
	struct sshbuf *msg;
	int r, constrained = (life || confirm);
	u_char type;

	if (add) {
		type = constrained ?
		    SSH_AGENTC_ADD_SMARTCARD_KEY_CONSTRAINED :
		    SSH_AGENTC_ADD_SMARTCARD_KEY;
	} else
		type = SSH_AGENTC_REMOVE_SMARTCARD_KEY;

	if ((msg = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_put_u8(msg, type)) != 0 ||
	    (r = sshbuf_put_cstring(msg, reader_id)) != 0 ||
	    (r = sshbuf_put_cstring(msg, pin)) != 0)
		goto out;
	if (constrained &&
	    (r = encode_constraints(msg, life, confirm, 0)) != 0)
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