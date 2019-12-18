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
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ HAL_REGWRITE ;

/* Variables and functions */
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath_hal_setregs(struct ath_hal *ah, const HAL_REGWRITE *regs, int space)
{
	while (space >= sizeof(HAL_REGWRITE)) {
		OS_REG_WRITE(ah, regs->addr, regs->value);
		regs++, space -= sizeof(HAL_REGWRITE);
	}
}