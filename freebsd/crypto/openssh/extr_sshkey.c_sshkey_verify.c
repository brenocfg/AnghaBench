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
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 size_t SSH_KEY_MAX_SIGN_DATA_SIZE ; 
 int ssh_dss_verify (struct sshkey const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int ssh_ecdsa_verify (struct sshkey const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int ssh_ed25519_verify (struct sshkey const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int ssh_rsa_verify (struct sshkey const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,char const*) ; 
 int ssh_xmss_verify (struct sshkey const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

int
sshkey_verify(const struct sshkey *key,
    const u_char *sig, size_t siglen,
    const u_char *data, size_t dlen, const char *alg, u_int compat)
{
	if (siglen == 0 || dlen > SSH_KEY_MAX_SIGN_DATA_SIZE)
		return SSH_ERR_INVALID_ARGUMENT;
	switch (key->type) {
#ifdef WITH_OPENSSL
	case KEY_DSA_CERT:
	case KEY_DSA:
		return ssh_dss_verify(key, sig, siglen, data, dlen, compat);
# ifdef OPENSSL_HAS_ECC
	case KEY_ECDSA_CERT:
	case KEY_ECDSA:
		return ssh_ecdsa_verify(key, sig, siglen, data, dlen, compat);
# endif /* OPENSSL_HAS_ECC */
	case KEY_RSA_CERT:
	case KEY_RSA:
		return ssh_rsa_verify(key, sig, siglen, data, dlen, alg);
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
	case KEY_ED25519_CERT:
		return ssh_ed25519_verify(key, sig, siglen, data, dlen, compat);
#ifdef WITH_XMSS
	case KEY_XMSS:
	case KEY_XMSS_CERT:
		return ssh_xmss_verify(key, sig, siglen, data, dlen, compat);
#endif /* WITH_XMSS */
	default:
		return SSH_ERR_KEY_TYPE_UNKNOWN;
	}
}