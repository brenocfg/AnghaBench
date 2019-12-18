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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_RSTN ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static int visstrim_camera_reset(struct device *dev)
{
	gpio_set_value(TVP5150_RSTN, 0);
	ndelay(500);
	gpio_set_value(TVP5150_RSTN, 1);

	return 0;
}