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
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ vtcon_pending_free ; 

__attribute__((used)) static void
vtcon_drain_all(void)
{
	int first;

	for (first = 1; vtcon_pending_free != 0; first = 0) {
		if (first != 0) {
			printf("virtio_console: Waiting for all detached TTY "
			    "devices to have open fds closed.\n");
		}
		pause("vtcondra", hz);
	}
}