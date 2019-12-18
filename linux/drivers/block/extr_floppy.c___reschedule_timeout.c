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
struct TYPE_2__ {unsigned long timeout; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,char const*) ; 
 int FD_DEBUG ; 
 unsigned long HZ ; 
 int N_DRIVE ; 
 TYPE_1__* UDP ; 
 int current_drive ; 
 int current_reqD ; 
 int /*<<< orphan*/  fd_timeout ; 
 int /*<<< orphan*/  floppy_wq ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 char const* timeout_message ; 

__attribute__((used)) static void __reschedule_timeout(int drive, const char *message)
{
	unsigned long delay;

	if (drive == current_reqD)
		drive = current_drive;

	if (drive < 0 || drive >= N_DRIVE) {
		delay = 20UL * HZ;
		drive = 0;
	} else
		delay = UDP->timeout;

	mod_delayed_work(floppy_wq, &fd_timeout, delay);
	if (UDP->flags & FD_DEBUG)
		DPRINT("reschedule timeout %s\n", message);
	timeout_message = message;
}