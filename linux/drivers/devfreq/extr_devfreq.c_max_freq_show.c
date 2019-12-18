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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  scaling_max_freq; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct devfreq* to_devfreq (struct device*) ; 

__attribute__((used)) static ssize_t max_freq_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct devfreq *df = to_devfreq(dev);

	return sprintf(buf, "%lu\n", min(df->scaling_max_freq, df->max_freq));
}