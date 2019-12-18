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
struct spacc_engine {int stat_irq_thresh; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct spacc_engine* spacc_dev_to_engine (struct device*) ; 

__attribute__((used)) static ssize_t spacc_stat_irq_thresh_show(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	struct spacc_engine *engine = spacc_dev_to_engine(dev);

	return snprintf(buf, PAGE_SIZE, "%u\n", engine->stat_irq_thresh);
}