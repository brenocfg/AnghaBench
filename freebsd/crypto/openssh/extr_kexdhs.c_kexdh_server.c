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

/* Variables and functions */
#define  KEX_DH_GRP14_SHA1 132 
#define  KEX_DH_GRP14_SHA256 131 
#define  KEX_DH_GRP16_SHA512 130 
#define  KEX_DH_GRP18_SHA512 129 
#define  KEX_DH_GRP1_SHA1 128 
 int /*<<< orphan*/  SSH2_MSG_KEXDH_INIT ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  debug (char*) ; 
 int dh_gen_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dh_new_group1 () ; 
 int /*<<< orphan*/ * dh_new_group14 () ; 
 int /*<<< orphan*/ * dh_new_group16 () ; 
 int /*<<< orphan*/ * dh_new_group18 () ; 
 int /*<<< orphan*/  input_kex_dh_init ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kexdh_server(struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	int r;

	/* generate server DH public key */
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
	if ((r = dh_gen_key(kex->dh, kex->we_need * 8)) != 0)
		goto out;

	debug("expecting SSH2_MSG_KEXDH_INIT");
	ssh_dispatch_set(ssh, SSH2_MSG_KEXDH_INIT, &input_kex_dh_init);
	r = 0;
 out:
	return r;
}