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
typedef  int u_int ;
struct ssh {struct kex* kex; } ;
struct kex {int dh_need; int min; int max; int nbits; } ;

/* Variables and functions */
 int DH_GRP_MAX ; 
 int DH_GRP_MIN ; 
 int MINIMUM (int,int) ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_DH_GEX_GROUP ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_DH_GEX_REQUEST ; 
 int SSH_BUG_DHGEX_LARGE ; 
 int datafellows ; 
 int /*<<< orphan*/  debug (char*,int,int,int) ; 
 int dh_estimate (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  input_kex_dh_gex_group ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sshpkt_put_u32 (struct ssh*,int) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
kexgex_client(struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	int r;
	u_int nbits;

	nbits = dh_estimate(kex->dh_need * 8);

	kex->min = DH_GRP_MIN;
	kex->max = DH_GRP_MAX;
	kex->nbits = nbits;
	if (datafellows & SSH_BUG_DHGEX_LARGE)
		kex->nbits = MINIMUM(kex->nbits, 4096);
	/* New GEX request */
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEX_DH_GEX_REQUEST)) != 0 ||
	    (r = sshpkt_put_u32(ssh, kex->min)) != 0 ||
	    (r = sshpkt_put_u32(ssh, kex->nbits)) != 0 ||
	    (r = sshpkt_put_u32(ssh, kex->max)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;
	debug("SSH2_MSG_KEX_DH_GEX_REQUEST(%u<%u<%u) sent",
	    kex->min, kex->nbits, kex->max);
#ifdef DEBUG_KEXDH
	fprintf(stderr, "\nmin = %d, nbits = %d, max = %d\n",
	    kex->min, kex->nbits, kex->max);
#endif
	ssh_dispatch_set(ssh, SSH2_MSG_KEX_DH_GEX_GROUP,
	    &input_kex_dh_gex_group);
	r = 0;
 out:
	return r;
}