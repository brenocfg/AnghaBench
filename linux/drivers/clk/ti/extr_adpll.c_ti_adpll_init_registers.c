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
struct ti_adpll_data {scalar_t__ iobase; scalar_t__ regs; TYPE_1__* c; } ;
struct TYPE_2__ {scalar_t__ is_type_s; } ;

/* Variables and functions */
 scalar_t__ ADPLL_PLLSS_MMR_LOCK_OFFSET ; 
 scalar_t__ ADPLL_PWRCTRL_OFFSET ; 
 int /*<<< orphan*/  ti_adpll_unlock_all (scalar_t__) ; 

__attribute__((used)) static int ti_adpll_init_registers(struct ti_adpll_data *d)
{
	int register_offset = 0;

	if (d->c->is_type_s) {
		register_offset = 8;
		ti_adpll_unlock_all(d->iobase + ADPLL_PLLSS_MMR_LOCK_OFFSET);
	}

	d->regs = d->iobase + register_offset + ADPLL_PWRCTRL_OFFSET;

	return 0;
}