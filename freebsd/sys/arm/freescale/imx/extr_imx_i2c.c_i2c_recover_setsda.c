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
struct i2c_softc {int /*<<< orphan*/  rb_sdapin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_pin_set_active (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
i2c_recover_setsda(void *ctx, int value)
{

	gpio_pin_set_active(((struct i2c_softc *)ctx)->rb_sdapin, value);
}