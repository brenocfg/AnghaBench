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
 int /*<<< orphan*/  DISPATCH_NONBLOCK ; 
 int /*<<< orphan*/  active_state ; 
 int /*<<< orphan*/  quit_pending ; 
 int /*<<< orphan*/  ssh_dispatch_run_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
client_process_buffered_input_packets(void)
{
	ssh_dispatch_run_fatal(active_state, DISPATCH_NONBLOCK, &quit_pending);
}