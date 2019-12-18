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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomicio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  can_output () ; 
 scalar_t__ cur_pos ; 
 scalar_t__ end_pos ; 
 int /*<<< orphan*/  refresh_progress_meter () ; 
 int /*<<< orphan*/  vwrite ; 

void
stop_progress_meter(void)
{
	alarm(0);

	if (!can_output())
		return;

	/* Ensure we complete the progress */
	if (cur_pos != end_pos)
		refresh_progress_meter();

	atomicio(vwrite, STDOUT_FILENO, "\n", 1);
}