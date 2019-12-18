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
 int /*<<< orphan*/  GPIO_READ_BACK ; 
 int /*<<< orphan*/  OLPC_GPIO_LID ; 
 int cs5535_gpio_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flip_lid_inverter () ; 
 int /*<<< orphan*/  lid_inverted ; 
 int lid_open ; 

__attribute__((used)) static void detect_lid_state(void)
{
	/*
	 * the edge detector hookup on the gpio inputs on the geode is
	 * odd, to say the least.  See http://dev.laptop.org/ticket/5703
	 * for details, but in a nutshell:  we don't use the edge
	 * detectors.  instead, we make use of an anomaly:  with the both
	 * edge detectors turned off, we still get an edge event on a
	 * positive edge transition.  to take advantage of this, we use the
	 * front-end inverter to ensure that that's the edge we're always
	 * going to see next.
	 */

	int state;

	state = cs5535_gpio_isset(OLPC_GPIO_LID, GPIO_READ_BACK);
	lid_open = !state ^ !lid_inverted; /* x ^^ y */
	if (!state)
		return;

	flip_lid_inverter();
}