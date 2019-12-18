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
struct gpio_desc {unsigned long config; unsigned long mask; unsigned long mux_mask; scalar_t__ can_wakeup; scalar_t__ keypad_gpio; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MFP_AF (unsigned long) ; 
 unsigned long MFP_LPM_CAN_WAKEUP ; 
 unsigned long MFP_LPM_EDGE_FALL ; 
 unsigned long MFP_LPM_EDGE_RISE ; 
 int /*<<< orphan*/  MFP_PIN_GPIO127 ; 
 unsigned long PFER ; 
 unsigned long PKWR ; 
 unsigned long PRER ; 
 unsigned long PWER ; 
 struct gpio_desc* gpio_desc ; 
 unsigned int mfp_to_gpio (int /*<<< orphan*/ ) ; 

int gpio_set_wake(unsigned int gpio, unsigned int on)
{
	struct gpio_desc *d;
	unsigned long c, mux_taken;

	if (gpio > mfp_to_gpio(MFP_PIN_GPIO127))
		return -EINVAL;

	d = &gpio_desc[gpio];
	c = d->config;

	if (!d->valid)
		return -EINVAL;

	/* Allow keypad GPIOs to wakeup system when
	 * configured as generic GPIOs.
	 */
	if (d->keypad_gpio && (MFP_AF(d->config) == 0) &&
	    (d->config & MFP_LPM_CAN_WAKEUP)) {
		if (on)
			PKWR |= d->mask;
		else
			PKWR &= ~d->mask;
		return 0;
	}

	mux_taken = (PWER & d->mux_mask) & (~d->mask);
	if (on && mux_taken)
		return -EBUSY;

	if (d->can_wakeup && (c & MFP_LPM_CAN_WAKEUP)) {
		if (on) {
			PWER = (PWER & ~d->mux_mask) | d->mask;

			if (c & MFP_LPM_EDGE_RISE)
				PRER |= d->mask;
			else
				PRER &= ~d->mask;

			if (c & MFP_LPM_EDGE_FALL)
				PFER |= d->mask;
			else
				PFER &= ~d->mask;
		} else {
			PWER &= ~d->mask;
			PRER &= ~d->mask;
			PFER &= ~d->mask;
		}
	}
	return 0;
}