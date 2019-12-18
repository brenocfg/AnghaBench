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

/* Variables and functions */
#define  H_CEDE 141 
#define  H_CONFER 140 
#define  H_CPPR 139 
#define  H_EOI 138 
#define  H_IPI 137 
#define  H_IPOLL 136 
#define  H_LOGICAL_CI_LOAD 135 
#define  H_LOGICAL_CI_STORE 134 
#define  H_PAGE_INIT 133 
#define  H_PROD 132 
#define  H_REGISTER_VPA 131 
#define  H_SET_MODE 130 
#define  H_XIRR 129 
#define  H_XIRR_X 128 
 int kvmppc_hcall_impl_hv_realmode (unsigned long) ; 

__attribute__((used)) static int kvmppc_hcall_impl_hv(unsigned long cmd)
{
	switch (cmd) {
	case H_CEDE:
	case H_PROD:
	case H_CONFER:
	case H_REGISTER_VPA:
	case H_SET_MODE:
	case H_LOGICAL_CI_LOAD:
	case H_LOGICAL_CI_STORE:
#ifdef CONFIG_KVM_XICS
	case H_XIRR:
	case H_CPPR:
	case H_EOI:
	case H_IPI:
	case H_IPOLL:
	case H_XIRR_X:
#endif
	case H_PAGE_INIT:
		return 1;
	}

	/* See if it's in the real-mode table */
	return kvmppc_hcall_impl_hv_realmode(cmd);
}