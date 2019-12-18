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
struct ar8327_led {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar8327_led_unregister (struct ar8327_led*) ; 
 int /*<<< orphan*/  kfree (struct ar8327_led*) ; 

__attribute__((used)) static void
ar8327_led_destroy(struct ar8327_led *aled)
{
	ar8327_led_unregister(aled);
	kfree(aled);
}