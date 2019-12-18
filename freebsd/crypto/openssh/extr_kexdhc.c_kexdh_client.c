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
struct ssh {struct kex* kex; } ;
struct kex {int kex_type; int we_need; int /*<<< orphan*/ * dh; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DHparams_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  KEX_DH_GRP14_SHA1 132 
#define  KEX_DH_GRP14_SHA256 131 
#define  KEX_DH_GRP16_SHA512 130 
#define  KEX_DH_GRP18_SHA512 129 
#define  KEX_DH_GRP1_SHA1 128 
 int /*<<< orphan*/  SSH2_MSG_KEXDH_INIT ; 
 int /*<<< orphan*/  SSH2_MSG_KEXDH_REPLY ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  debug (char*) ; 
 int dh_gen_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dh_new_group1 () ; 
 int /*<<< orphan*/ * dh_new_group14 () ; 
 int /*<<< orphan*/ * dh_new_group16 () ; 
 int /*<<< orphan*/ * dh_new_group18 () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  input_kex_dh ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sshpkt_put_bignum2 (struct ssh*,int /*<<< orphan*/  const*) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
kexdh_client(struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	int r;
	const BIGNUM *pub_key;

	/* generate and send 'e', client DH public key */
	switch (kex->kex_type) {
	case KEX_DH_GRP1_SHA1:
		kex->dh = dh_new_group1();
		break;
	case KEX_DH_GRP14_SHA1:
	case KEX_DH_GRP14_SHA256:
		kex->dh = dh_new_group14();
		break;
	case KEX_DH_GRP16_SHA512:
		kex->dh = dh_new_group16();
		break;
	case KEX_DH_GRP18_SHA512:
		kex->dh = dh_new_group18();
		break;
	default:
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}
	if (kex->dh == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	debug("sending SSH2_MSG_KEXDH_INIT");
	if ((r = dh_gen_key(kex->dh, kex->we_need * 8)) != 0)
		goto out;
	DH_get0_key(kex->dh, &pub_key, NULL);
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEXDH_INIT)) != 0 ||
	    (r = sshpkt_put_bignum2(ssh, pub_key)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;
#ifdef DEBUG_KEXDH
	DHparams_print_fp(stderr, kex->dh);
	fprintf(stderr, "pub= ");
	BN_print_fp(stderr, pub_key);
	fprintf(stderr, "\n");
#endif
	debug("expecting SSH2_MSG_KEXDH_REPLY");
	ssh_dispatch_set(ssh, SSH2_MSG_KEXDH_REPLY, &input_kex_dh);
	r = 0;
 out:
	return r;
}