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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_AF ; 
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RO ; 
 int ATTR_AP_RW_BIT ; 
 int ATTR_SW_DBM ; 
 int ESR_ELx_EXCEPTION (int) ; 
#define  EXCP_DATA_ABORT 141 
#define  EXCP_DATA_ABORT_L 140 
#define  EXCP_INSN_ABORT 139 
#define  EXCP_INSN_ABORT_L 138 
#define  ISS_DATA_DFSC_AFF_L1 137 
#define  ISS_DATA_DFSC_AFF_L2 136 
#define  ISS_DATA_DFSC_AFF_L3 135 
 int ISS_DATA_DFSC_MASK ; 
#define  ISS_DATA_DFSC_PF_L1 134 
#define  ISS_DATA_DFSC_PF_L2 133 
#define  ISS_DATA_DFSC_PF_L3 132 
#define  ISS_DATA_DFSC_TF_L0 131 
#define  ISS_DATA_DFSC_TF_L1 130 
#define  ISS_DATA_DFSC_TF_L2 129 
#define  ISS_DATA_DFSC_TF_L3 128 
 int ISS_DATA_WnR ; 
 int KERN_FAILURE ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  PAR_SUCCESS (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int arm64_address_translate_s1e0r (int) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_clear_bits (int*,int) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_kextract (int) ; 
 int pmap_load (int*) ; 
 int* pmap_pte (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pmap_set_bits (int*,int /*<<< orphan*/ ) ; 

int
pmap_fault(pmap_t pmap, uint64_t esr, uint64_t far)
{
	pt_entry_t pte, *ptep;
	register_t intr;
	uint64_t ec, par;
	int lvl, rv;

	rv = KERN_FAILURE;

	ec = ESR_ELx_EXCEPTION(esr);
	switch (ec) {
	case EXCP_INSN_ABORT_L:
	case EXCP_INSN_ABORT:
	case EXCP_DATA_ABORT_L:
	case EXCP_DATA_ABORT:
		break;
	default:
		return (rv);
	}

	/* Data and insn aborts use same encoding for FSC field. */
	switch (esr & ISS_DATA_DFSC_MASK) {
	case ISS_DATA_DFSC_AFF_L1:
	case ISS_DATA_DFSC_AFF_L2:
	case ISS_DATA_DFSC_AFF_L3:
		PMAP_LOCK(pmap);
		ptep = pmap_pte(pmap, far, &lvl);
		if (ptep != NULL) {
			pmap_set_bits(ptep, ATTR_AF);
			rv = KERN_SUCCESS;
			/*
			 * XXXMJ as an optimization we could mark the entry
			 * dirty if this is a write fault.
			 */
		}
		PMAP_UNLOCK(pmap);
		break;
	case ISS_DATA_DFSC_PF_L1:
	case ISS_DATA_DFSC_PF_L2:
	case ISS_DATA_DFSC_PF_L3:
		if ((ec != EXCP_DATA_ABORT_L && ec != EXCP_DATA_ABORT) ||
		    (esr & ISS_DATA_WnR) == 0)
			return (rv);
		PMAP_LOCK(pmap);
		ptep = pmap_pte(pmap, far, &lvl);
		if (ptep != NULL &&
		    ((pte = pmap_load(ptep)) & ATTR_SW_DBM) != 0) {
			if ((pte & ATTR_AP_RW_BIT) == ATTR_AP(ATTR_AP_RO)) {
				pmap_clear_bits(ptep, ATTR_AP_RW_BIT);
				pmap_invalidate_page(pmap, far);
			}
			rv = KERN_SUCCESS;
		}
		PMAP_UNLOCK(pmap);
		break;
	case ISS_DATA_DFSC_TF_L0:
	case ISS_DATA_DFSC_TF_L1:
	case ISS_DATA_DFSC_TF_L2:
	case ISS_DATA_DFSC_TF_L3:
		/*
		 * Retry the translation.  A break-before-make sequence can
		 * produce a transient fault.
		 */
		if (pmap == kernel_pmap) {
			/*
			 * The translation fault may have occurred within a
			 * critical section.  Therefore, we must check the
			 * address without acquiring the kernel pmap's lock.
			 */
			if (pmap_kextract(far) != 0)
				rv = KERN_SUCCESS;
		} else {
			PMAP_LOCK(pmap);
			/* Ask the MMU to check the address. */
			intr = intr_disable();
			par = arm64_address_translate_s1e0r(far);
			intr_restore(intr);
			PMAP_UNLOCK(pmap);

			/*
			 * If the translation was successful, then we can
			 * return success to the trap handler.
			 */
			if (PAR_SUCCESS(par))
				rv = KERN_SUCCESS;
		}
		break;
	}

	return (rv);
}