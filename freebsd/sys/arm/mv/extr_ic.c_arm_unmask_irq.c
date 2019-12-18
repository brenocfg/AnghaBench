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
struct TYPE_2__ {scalar_t__ ic_error_regs; scalar_t__ ic_high_regs; } ;

/* Variables and functions */
 int mv_ic_get_mask () ; 
 int mv_ic_get_mask_error () ; 
 int mv_ic_get_mask_hi () ; 
 TYPE_1__* mv_ic_sc ; 
 int /*<<< orphan*/  mv_ic_set_mask (int) ; 
 int /*<<< orphan*/  mv_ic_set_mask_error (int) ; 
 int /*<<< orphan*/  mv_ic_set_mask_hi (int) ; 

void
arm_unmask_irq(uintptr_t nb)
{
	uint32_t	mr;

	if (nb < 32) {
		mr = mv_ic_get_mask();
		mr |= (1 << nb);
		mv_ic_set_mask(mr);

	} else if ((nb < 64) && mv_ic_sc->ic_high_regs) {
		mr = mv_ic_get_mask_hi();
		mr |= (1 << (nb - 32));
		mv_ic_set_mask_hi(mr);

	} else if ((nb < 96) && mv_ic_sc->ic_error_regs) {
		mr = mv_ic_get_mask_error();
		mr |= (1 << (nb - 64));
		mv_ic_set_mask_error(mr);
	}
}