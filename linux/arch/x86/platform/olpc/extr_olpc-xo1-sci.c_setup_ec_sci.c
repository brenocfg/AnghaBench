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
 int /*<<< orphan*/  GPIO_EVENTS_ENABLE ; 
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_STS ; 
 int /*<<< orphan*/  GPIO_POSITIVE_EDGE_STS ; 
 int /*<<< orphan*/  OLPC_GPIO_ECSCI ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_setup_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cs5535_pic_unreqz_select_high (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sci_irq ; 

__attribute__((used)) static int setup_ec_sci(void)
{
	int r;

	r = gpio_request(OLPC_GPIO_ECSCI, "OLPC-ECSCI");
	if (r)
		return r;

	gpio_direction_input(OLPC_GPIO_ECSCI);

	/* Clear pending EC SCI events */
	cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_POSITIVE_EDGE_STS);

	/*
	 * Enable EC SCI events, and map them to both a PME and the SCI
	 * interrupt.
	 *
	 * Ordinarily, in addition to functioning as GPIOs, Geode GPIOs can
	 * be mapped to regular interrupts *or* Geode-specific Power
	 * Management Events (PMEs) - events that bring the system out of
	 * suspend. In this case, we want both of those things - the system
	 * wakeup, *and* the ability to get an interrupt when an event occurs.
	 *
	 * To achieve this, we map the GPIO to a PME, and then we use one
	 * of the many generic knobs on the CS5535 PIC to additionally map the
	 * PME to the regular SCI interrupt line.
	 */
	cs5535_gpio_set(OLPC_GPIO_ECSCI, GPIO_EVENTS_ENABLE);

	/* Set the SCI to cause a PME event on group 7 */
	cs5535_gpio_setup_event(OLPC_GPIO_ECSCI, 7, 1);

	/* And have group 7 also fire the SCI interrupt */
	cs5535_pic_unreqz_select_high(7, sci_irq);

	return 0;
}