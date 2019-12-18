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
typedef  int /*<<< orphan*/  pgprotval_t ;

/* Variables and functions */
 int PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PAGE_RW ; 
 int /*<<< orphan*/  __end_rodata ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __start_rodata ; 
 scalar_t__ kernel_set_to_readonly ; 
 scalar_t__ overlaps (unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static pgprotval_t protect_rodata(unsigned long spfn, unsigned long epfn)
{
	unsigned long epfn_ro, spfn_ro = PFN_DOWN(__pa_symbol(__start_rodata));

	/*
	 * Note: __end_rodata is at page aligned and not inclusive, so
	 * subtract 1 to get the last enforced PFN in the rodata area.
	 */
	epfn_ro = PFN_DOWN(__pa_symbol(__end_rodata)) - 1;

	if (kernel_set_to_readonly && overlaps(spfn, epfn, spfn_ro, epfn_ro))
		return _PAGE_RW;
	return 0;
}