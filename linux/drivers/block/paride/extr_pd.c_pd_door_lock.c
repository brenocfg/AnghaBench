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
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DOORLOCK ; 
 int Ok ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  STAT_READY ; 
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pd_wait_for (struct pd_unit*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum action pd_door_lock(struct pd_unit *disk)
{
	if (!(pd_wait_for(disk, STAT_READY, "Lock") & STAT_ERR)) {
		pd_send_command(disk, 1, 0, 0, 0, 0, IDE_DOORLOCK);
		pd_wait_for(disk, STAT_READY, "Lock done");
	}
	return Ok;
}