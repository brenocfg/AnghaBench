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
 int /*<<< orphan*/  AU1000_SYS_WAKEMSK ; 
 int /*<<< orphan*/  AU1000_SYS_WAKESRC ; 
 int /*<<< orphan*/  alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db1x_pm_last_wakesrc ; 

__attribute__((used)) static void db1x_pm_end(void)
{
	/* read and store wakeup source, the clear the register. To
	 * be able to clear it, WAKEMSK must be cleared first.
	 */
	db1x_pm_last_wakesrc = alchemy_rdsys(AU1000_SYS_WAKESRC);

	alchemy_wrsys(0, AU1000_SYS_WAKEMSK);
	alchemy_wrsys(0, AU1000_SYS_WAKESRC);
}