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
struct pd_unit {scalar_t__ heads; int /*<<< orphan*/  sectors; } ;

/* Variables and functions */
 char* DBMSG (char*) ; 
 int /*<<< orphan*/  IDE_INIT_DEV_PARMS ; 
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_wait_for (struct pd_unit*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pd_init_dev_parms(struct pd_unit *disk)
{
	pd_wait_for(disk, 0, DBMSG("before init_dev_parms"));
	pd_send_command(disk, disk->sectors, 0, disk->heads - 1, 0, 0,
			IDE_INIT_DEV_PARMS);
	udelay(300);
	pd_wait_for(disk, 0, "Initialise device parameters");
}