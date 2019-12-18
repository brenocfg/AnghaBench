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
struct pd_unit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBMSG (char*) ; 
 int /*<<< orphan*/  IDE_STANDBY ; 
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_wait_for (struct pd_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pd_standby_off(struct pd_unit *disk)
{
	pd_wait_for(disk, 0, DBMSG("before STANDBY"));
	pd_send_command(disk, 0, 0, 0, 0, 0, IDE_STANDBY);
	pd_wait_for(disk, 0, DBMSG("after STANDBY"));
}