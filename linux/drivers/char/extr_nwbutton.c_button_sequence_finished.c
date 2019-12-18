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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NWBUTTON_REBOOT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  bcount ; 
 int /*<<< orphan*/  button_consume_callbacks (scalar_t__) ; 
 int /*<<< orphan*/  button_output_buffer ; 
 scalar_t__ button_press_count ; 
 int /*<<< orphan*/  button_wait_queue ; 
 int /*<<< orphan*/  kill_cad_pid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reboot_count ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void button_sequence_finished(struct timer_list *unused)
{
	if (IS_ENABLED(CONFIG_NWBUTTON_REBOOT) &&
	    button_press_count == reboot_count)
		kill_cad_pid(SIGINT, 1);	/* Ask init to reboot us */
	button_consume_callbacks (button_press_count);
	bcount = sprintf (button_output_buffer, "%d\n", button_press_count);
	button_press_count = 0;		/* Reset the button press counter */
	wake_up_interruptible (&button_wait_queue);
}