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
struct devfreq_event_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfreq_event_remove_edev (struct devfreq_event_dev*) ; 

__attribute__((used)) static void devm_devfreq_event_release(struct device *dev, void *res)
{
	devfreq_event_remove_edev(*(struct devfreq_event_dev **)res);
}