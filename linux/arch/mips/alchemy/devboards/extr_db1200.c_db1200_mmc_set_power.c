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
 int /*<<< orphan*/  BCSR_BOARD ; 
 int /*<<< orphan*/  BCSR_BOARD_SD0PWR ; 
 int /*<<< orphan*/  bcsr_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void db1200_mmc_set_power(void *mmc_host, int state)
{
	if (state) {
		bcsr_mod(BCSR_BOARD, 0, BCSR_BOARD_SD0PWR);
		msleep(400);	/* stabilization time */
	} else
		bcsr_mod(BCSR_BOARD, BCSR_BOARD_SD0PWR, 0);
}