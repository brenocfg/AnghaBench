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
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  UPDATE_INTERVAL ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ can_output () ; 
 int errno ; 
 int /*<<< orphan*/  refresh_progress_meter () ; 
 int /*<<< orphan*/  setscreensize () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 scalar_t__ win_resized ; 

__attribute__((used)) static void
update_progress_meter(int ignore)
{
	int save_errno;

	save_errno = errno;

	if (win_resized) {
		setscreensize();
		win_resized = 0;
	}
	if (can_output())
		refresh_progress_meter();

	signal(SIGALRM, update_progress_meter);
	alarm(UPDATE_INTERVAL);
	errno = save_errno;
}