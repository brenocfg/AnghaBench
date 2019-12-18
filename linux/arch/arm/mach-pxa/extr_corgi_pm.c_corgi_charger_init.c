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
 int /*<<< orphan*/  ARRAY_AND_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charger_gpios ; 
 int /*<<< orphan*/  gpio_request_array (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void corgi_charger_init(void)
{
	gpio_request_array(ARRAY_AND_SIZE(charger_gpios));
}