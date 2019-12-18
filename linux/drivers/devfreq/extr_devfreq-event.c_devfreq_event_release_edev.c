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
 int /*<<< orphan*/  kfree (struct devfreq_event_dev*) ; 
 struct devfreq_event_dev* to_devfreq_event (struct device*) ; 

__attribute__((used)) static void devfreq_event_release_edev(struct device *dev)
{
	struct devfreq_event_dev *edev = to_devfreq_event(dev);

	kfree(edev);
}