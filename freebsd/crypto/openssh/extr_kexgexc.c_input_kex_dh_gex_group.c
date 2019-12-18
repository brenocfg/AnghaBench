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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_int ;
struct ssh {struct kex* kex; } ;
struct kex {scalar_t__ min; scalar_t__ max; int we_need; int /*<<< orphan*/ * dh; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DHparams_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_DH_GEX_GROUP ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_DH_GEX_INIT ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_DH_GEX_REPLY ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_DH_GEX_OUT_OF_RANGE ; 
 int /*<<< orphan*/  debug (char*) ; 
 int dh_gen_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dh_new_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  input_kex_dh_gex_reply ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sshpkt_get_bignum2 (struct ssh*,int /*<<< orphan*/ *) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_put_bignum2 (struct ssh*,int /*<<< orphan*/  const*) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
input_kex_dh_gex_group(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	BIGNUM *p = NULL, *g = NULL;
	const BIGNUM *pub_key;
	int r, bits;

	debug("got SSH2_MSG_KEX_DH_GEX_GROUP");

	if ((p = BN_new()) == NULL ||
	    (g = BN_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = sshpkt_get_bignum2(ssh, p)) != 0 ||
	    (r = sshpkt_get_bignum2(ssh, g)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;
	if ((bits = BN_num_bits(p)) < 0 ||
	    (u_int)bits < kex->min || (u_int)bits > kex->max) {
		r = SSH_ERR_DH_GEX_OUT_OF_RANGE;
		goto out;
	}
	if ((kex->dh = dh_new_group(g, p)) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	p = g = NULL; /* belong to kex->dh now */

	/* generate and send 'e', client DH public key */
	if ((r = dh_gen_key(kex->dh, kex->we_need * 8)) != 0)
		goto out;
	DH_get0_key(kex->dh, &pub_key, NULL);
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEX_DH_GEX_INIT)) != 0 ||
	    (r = sshpkt_put_bignum2(ssh, pub_key)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;
	debug("SSH2_MSG_KEX_DH_GEX_INIT sent");
#ifdef DEBUG_KEXDH
	DHparams_print_fp(stderr, kex->dh);
	fprintf(stderr, "pub= ");
	BN_print_fp(stderr, pub_key);
	fprintf(stderr, "\n");
#endif
	ssh_dispatch_set(ssh, SSH2_MSG_KEX_DH_GEX_GROUP, NULL);
	ssh_dispatch_set(ssh, SSH2_MSG_KEX_DH_GEX_REPLY, &input_kex_dh_gex_reply);
	r = 0;
out:
	BN_clear_free(p);
	BN_clear_free(g);
	return r;
}