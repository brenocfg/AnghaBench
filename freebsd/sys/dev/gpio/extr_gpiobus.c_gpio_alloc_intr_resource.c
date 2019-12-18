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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */

struct resource *
gpio_alloc_intr_resource(device_t consumer_dev, int *rid, u_int alloc_flags,
    gpio_pin_t pin, uint32_t intr_mode)
{

	return (NULL);
}