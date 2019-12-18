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
 int /*<<< orphan*/  MAXTIMEOUT ; 
 int /*<<< orphan*/  command_done ; 
 int command_status ; 
 int /*<<< orphan*/ * cont ; 
 int /*<<< orphan*/  reschedule_timeout (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_wakeup(void)
{
	reschedule_timeout(MAXTIMEOUT, "do wakeup");
	cont = NULL;
	command_status += 2;
	wake_up(&command_done);
}