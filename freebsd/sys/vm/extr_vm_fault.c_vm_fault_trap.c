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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ vm_map_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_osrel; } ;

/* Variables and functions */
 int BUS_OBJERR ; 
 int BUS_OOMERR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  KERN_FAILURE 132 
#define  KERN_INVALID_ADDRESS 131 
#define  KERN_OUT_OF_BOUNDS 130 
#define  KERN_PROTECTION_FAILURE 129 
#define  KERN_RESOURCE_SHORTAGE 128 
 int KERN_SUCCESS ; 
 scalar_t__ KTRPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_FAULT ; 
 int /*<<< orphan*/  KTR_FAULTEND ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  P_OSREL_SIGSEGV ; 
 int SEGV_ACCERR ; 
 int SEGV_MAPERR ; 
 int SIGBUS ; 
 int SIGSEGV ; 
 int /*<<< orphan*/  SV_ABI_FREEBSD ; 
 int /*<<< orphan*/  SV_CURPROC_ABI () ; 
 int UCODE_PAGEFLT ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ kernel_map ; 
 int /*<<< orphan*/  ktrfault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrfaultend (int) ; 
 int prot_fault_translation ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 
 int vm_fault (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
vm_fault_trap(vm_map_t map, vm_offset_t vaddr, vm_prot_t fault_type,
    int fault_flags, int *signo, int *ucode)
{
	int result;

	MPASS(signo == NULL || ucode != NULL);
#ifdef KTRACE
	if (map != kernel_map && KTRPOINT(curthread, KTR_FAULT))
		ktrfault(vaddr, fault_type);
#endif
	result = vm_fault(map, trunc_page(vaddr), fault_type, fault_flags,
	    NULL);
	KASSERT(result == KERN_SUCCESS || result == KERN_FAILURE ||
	    result == KERN_INVALID_ADDRESS ||
	    result == KERN_RESOURCE_SHORTAGE ||
	    result == KERN_PROTECTION_FAILURE ||
	    result == KERN_OUT_OF_BOUNDS,
	    ("Unexpected Mach error %d from vm_fault()", result));
#ifdef KTRACE
	if (map != kernel_map && KTRPOINT(curthread, KTR_FAULTEND))
		ktrfaultend(result);
#endif
	if (result != KERN_SUCCESS && signo != NULL) {
		switch (result) {
		case KERN_FAILURE:
		case KERN_INVALID_ADDRESS:
			*signo = SIGSEGV;
			*ucode = SEGV_MAPERR;
			break;
		case KERN_RESOURCE_SHORTAGE:
			*signo = SIGBUS;
			*ucode = BUS_OOMERR;
			break;
		case KERN_OUT_OF_BOUNDS:
			*signo = SIGBUS;
			*ucode = BUS_OBJERR;
			break;
		case KERN_PROTECTION_FAILURE:
			if (prot_fault_translation == 0) {
				/*
				 * Autodetect.  This check also covers
				 * the images without the ABI-tag ELF
				 * note.
				 */
				if (SV_CURPROC_ABI() == SV_ABI_FREEBSD &&
				    curproc->p_osrel >= P_OSREL_SIGSEGV) {
					*signo = SIGSEGV;
					*ucode = SEGV_ACCERR;
				} else {
					*signo = SIGBUS;
					*ucode = UCODE_PAGEFLT;
				}
			} else if (prot_fault_translation == 1) {
				/* Always compat mode. */
				*signo = SIGBUS;
				*ucode = UCODE_PAGEFLT;
			} else {
				/* Always SIGSEGV mode. */
				*signo = SIGSEGV;
				*ucode = SEGV_ACCERR;
			}
			break;
		default:
			KASSERT(0, ("Unexpected Mach error %d from vm_fault()",
			    result));
			break;
		}
	}
	return (result);
}