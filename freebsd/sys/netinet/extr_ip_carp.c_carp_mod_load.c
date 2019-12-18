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
struct protosw {int dummy; } ;

/* Variables and functions */
 size_t CARP_INET ; 
 size_t CARP_INET6 ; 
 int /*<<< orphan*/  IPPROTO_CARP ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  carp_attach ; 
 int /*<<< orphan*/  carp_attach_p ; 
 int /*<<< orphan*/  carp_demote_adj ; 
 int /*<<< orphan*/  carp_demote_adj_p ; 
 int /*<<< orphan*/  carp_detach ; 
 int /*<<< orphan*/  carp_detach_p ; 
 int /*<<< orphan*/  carp_forus ; 
 int /*<<< orphan*/  carp_forus_p ; 
 int /*<<< orphan*/  carp_get_vhid ; 
 int /*<<< orphan*/  carp_get_vhid_p ; 
 int /*<<< orphan*/  carp_iamatch ; 
 int /*<<< orphan*/  carp_iamatch6 ; 
 int /*<<< orphan*/  carp_iamatch6_p ; 
 int /*<<< orphan*/  carp_iamatch_p ; 
 int /*<<< orphan*/  carp_ioctl ; 
 int /*<<< orphan*/  carp_ioctl_p ; 
 int /*<<< orphan*/  carp_linkstate ; 
 int /*<<< orphan*/  carp_linkstate_p ; 
 int /*<<< orphan*/  carp_list ; 
 int /*<<< orphan*/  carp_macmatch6 ; 
 int /*<<< orphan*/  carp_macmatch6_p ; 
 int /*<<< orphan*/  carp_master ; 
 int /*<<< orphan*/  carp_master_p ; 
 int /*<<< orphan*/  carp_mod_cleanup () ; 
 int /*<<< orphan*/  carp_mtx ; 
 int /*<<< orphan*/  carp_output ; 
 int /*<<< orphan*/  carp_output_p ; 
 int /*<<< orphan*/  carp_sx ; 
 int /*<<< orphan*/  in6_carp_protosw ; 
 struct protosw in_carp_protosw ; 
 int ip6proto_register (int /*<<< orphan*/ ) ; 
 int ipproto_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pf_proto_register (int /*<<< orphan*/ ,struct protosw*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int* proto_reg ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
carp_mod_load(void)
{
	int err;

	mtx_init(&carp_mtx, "carp_mtx", NULL, MTX_DEF);
	sx_init(&carp_sx, "carp_sx");
	LIST_INIT(&carp_list);
	carp_get_vhid_p = carp_get_vhid;
	carp_forus_p = carp_forus;
	carp_output_p = carp_output;
	carp_linkstate_p = carp_linkstate;
	carp_ioctl_p = carp_ioctl;
	carp_attach_p = carp_attach;
	carp_detach_p = carp_detach;
	carp_demote_adj_p = carp_demote_adj;
	carp_master_p = carp_master;
#ifdef INET6
	carp_iamatch6_p = carp_iamatch6;
	carp_macmatch6_p = carp_macmatch6;
	proto_reg[CARP_INET6] = pf_proto_register(PF_INET6,
	    (struct protosw *)&in6_carp_protosw);
	if (proto_reg[CARP_INET6]) {
		printf("carp: error %d attaching to PF_INET6\n",
		    proto_reg[CARP_INET6]);
		carp_mod_cleanup();
		return (proto_reg[CARP_INET6]);
	}
	err = ip6proto_register(IPPROTO_CARP);
	if (err) {
		printf("carp: error %d registering with INET6\n", err);
		carp_mod_cleanup();
		return (err);
	}
#endif
#ifdef INET
	carp_iamatch_p = carp_iamatch;
	proto_reg[CARP_INET] = pf_proto_register(PF_INET, &in_carp_protosw);
	if (proto_reg[CARP_INET]) {
		printf("carp: error %d attaching to PF_INET\n",
		    proto_reg[CARP_INET]);
		carp_mod_cleanup();
		return (proto_reg[CARP_INET]);
	}
	err = ipproto_register(IPPROTO_CARP);
	if (err) {
		printf("carp: error %d registering with INET\n", err);
		carp_mod_cleanup();
		return (err);
	}
#endif
	return (0);
}