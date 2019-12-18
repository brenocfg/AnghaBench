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
struct pdc_mem_read_pdt {int dummy; } ;

/* Variables and functions */
 int PDC_ERROR ; 
 int /*<<< orphan*/  PDC_MEM ; 
 int /*<<< orphan*/  PDC_MEM_READ_PDT ; 
 int PDC_OK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __pa (unsigned long*) ; 
 int /*<<< orphan*/  convert_to_wide (unsigned long*) ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct pdc_mem_read_pdt*,unsigned long*,int) ; 
 scalar_t__ parisc_narrow_firmware ; 
 int /*<<< orphan*/  pdc_lock ; 
 unsigned long* pdc_result ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_mem_pdt_read_entries(struct pdc_mem_read_pdt *pret,
		unsigned long *pdt_entries_ptr)
{
	int retval;
	unsigned long flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_MEM, PDC_MEM_READ_PDT, __pa(pdc_result),
			__pa(pdt_entries_ptr));
	if (retval == PDC_OK) {
		convert_to_wide(pdc_result);
		memcpy(pret, pdc_result, sizeof(*pret));
	}
	spin_unlock_irqrestore(&pdc_lock, flags);

#ifdef CONFIG_64BIT
	/*
	 * 64-bit kernels should not call this PDT function in narrow mode.
	 * The pdt_entries_ptr array above will now contain 32-bit values
	 */
	if (WARN_ON_ONCE((retval == PDC_OK) && parisc_narrow_firmware))
		return PDC_ERROR;
#endif

	return retval;
}