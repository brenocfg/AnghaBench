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
struct counter_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_unregister (struct counter_device*) ; 

__attribute__((used)) static void devm_counter_unreg(struct device *dev, void *res)
{
	counter_unregister(*(struct counter_device **)res);
}