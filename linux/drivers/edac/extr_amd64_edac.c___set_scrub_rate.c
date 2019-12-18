#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct amd64_pvt {int fam; int model; int /*<<< orphan*/  F3; int /*<<< orphan*/  F2; } ;
struct TYPE_3__ {scalar_t__ scrubval; scalar_t__ bandwidth; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  F15H_M60H_SCRCTRL ; 
 int /*<<< orphan*/  SCRCTRL ; 
 int /*<<< orphan*/  __f17h_set_scrubval (struct amd64_pvt*,scalar_t__) ; 
 int /*<<< orphan*/  f15h_select_dct (struct amd64_pvt*,int) ; 
 int /*<<< orphan*/  pci_write_bits32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_1__* scrubrates ; 

__attribute__((used)) static int __set_scrub_rate(struct amd64_pvt *pvt, u32 new_bw, u32 min_rate)
{
	u32 scrubval;
	int i;

	/*
	 * map the configured rate (new_bw) to a value specific to the AMD64
	 * memory controller and apply to register. Search for the first
	 * bandwidth entry that is greater or equal than the setting requested
	 * and program that. If at last entry, turn off DRAM scrubbing.
	 *
	 * If no suitable bandwidth is found, turn off DRAM scrubbing entirely
	 * by falling back to the last element in scrubrates[].
	 */
	for (i = 0; i < ARRAY_SIZE(scrubrates) - 1; i++) {
		/*
		 * skip scrub rates which aren't recommended
		 * (see F10 BKDG, F3x58)
		 */
		if (scrubrates[i].scrubval < min_rate)
			continue;

		if (scrubrates[i].bandwidth <= new_bw)
			break;
	}

	scrubval = scrubrates[i].scrubval;

	if (pvt->fam == 0x17 || pvt->fam == 0x18) {
		__f17h_set_scrubval(pvt, scrubval);
	} else if (pvt->fam == 0x15 && pvt->model == 0x60) {
		f15h_select_dct(pvt, 0);
		pci_write_bits32(pvt->F2, F15H_M60H_SCRCTRL, scrubval, 0x001F);
		f15h_select_dct(pvt, 1);
		pci_write_bits32(pvt->F2, F15H_M60H_SCRCTRL, scrubval, 0x001F);
	} else {
		pci_write_bits32(pvt->F3, SCRCTRL, scrubval, 0x001F);
	}

	if (scrubval)
		return scrubrates[i].bandwidth;

	return 0;
}