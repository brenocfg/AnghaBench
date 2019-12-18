#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vmx {TYPE_1__* cap; struct vmcs* vmcs; } ;
struct vmcs {int dummy; } ;
struct TYPE_2__ {int proc_ctls; int proc_ctls2; int set; } ;

/* Variables and functions */
 int ENOENT ; 
 int PROCBASED2_ENABLE_INVPCID ; 
 int PROCBASED2_UNRESTRICTED_GUEST ; 
 int PROCBASED_HLT_EXITING ; 
 int PROCBASED_MTF ; 
 int PROCBASED_PAUSE_EXITING ; 
 int /*<<< orphan*/  VMCLEAR (struct vmcs*) ; 
 int VMCS_PRI_PROC_BASED_CTLS ; 
 int VMCS_SEC_PROC_BASED_CTLS ; 
 int /*<<< orphan*/  VMPTRLD (struct vmcs*) ; 
#define  VM_CAP_ENABLE_INVPCID 132 
#define  VM_CAP_HALT_EXIT 131 
#define  VM_CAP_MTRAP_EXIT 130 
#define  VM_CAP_PAUSE_EXIT 129 
#define  VM_CAP_UNRESTRICTED_GUEST 128 
 int /*<<< orphan*/  cap_halt_exit ; 
 int /*<<< orphan*/  cap_invpcid ; 
 int /*<<< orphan*/  cap_monitor_trap ; 
 int /*<<< orphan*/  cap_pause_exit ; 
 int /*<<< orphan*/  cap_unrestricted_guest ; 
 int vmwrite (int,int) ; 

__attribute__((used)) static int
vmx_setcap(void *arg, int vcpu, int type, int val)
{
	struct vmx *vmx = arg;
	struct vmcs *vmcs = &vmx->vmcs[vcpu];
	uint32_t baseval;
	uint32_t *pptr;
	int error;
	int flag;
	int reg;
	int retval;

	retval = ENOENT;
	pptr = NULL;

	switch (type) {
	case VM_CAP_HALT_EXIT:
		if (cap_halt_exit) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls;
			baseval = *pptr;
			flag = PROCBASED_HLT_EXITING;
			reg = VMCS_PRI_PROC_BASED_CTLS;
		}
		break;
	case VM_CAP_MTRAP_EXIT:
		if (cap_monitor_trap) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls;
			baseval = *pptr;
			flag = PROCBASED_MTF;
			reg = VMCS_PRI_PROC_BASED_CTLS;
		}
		break;
	case VM_CAP_PAUSE_EXIT:
		if (cap_pause_exit) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls;
			baseval = *pptr;
			flag = PROCBASED_PAUSE_EXITING;
			reg = VMCS_PRI_PROC_BASED_CTLS;
		}
		break;
	case VM_CAP_UNRESTRICTED_GUEST:
		if (cap_unrestricted_guest) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls2;
			baseval = *pptr;
			flag = PROCBASED2_UNRESTRICTED_GUEST;
			reg = VMCS_SEC_PROC_BASED_CTLS;
		}
		break;
	case VM_CAP_ENABLE_INVPCID:
		if (cap_invpcid) {
			retval = 0;
			pptr = &vmx->cap[vcpu].proc_ctls2;
			baseval = *pptr;
			flag = PROCBASED2_ENABLE_INVPCID;
			reg = VMCS_SEC_PROC_BASED_CTLS;
		}
		break;
	default:
		break;
	}

	if (retval == 0) {
		if (val) {
			baseval |= flag;
		} else {
			baseval &= ~flag;
		}
		VMPTRLD(vmcs);
		error = vmwrite(reg, baseval);
		VMCLEAR(vmcs);

		if (error) {
			retval = error;
		} else {
			/*
			 * Update optional stored flags, and record
			 * setting
			 */
			if (pptr != NULL) {
				*pptr = baseval;
			}

			if (val) {
				vmx->cap[vcpu].set |= (1 << type);
			} else {
				vmx->cap[vcpu].set &= ~(1 << type);
			}
		}
	}

	return (retval);
}