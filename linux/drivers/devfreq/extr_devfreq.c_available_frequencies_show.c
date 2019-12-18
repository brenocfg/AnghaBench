#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {int /*<<< orphan*/  lock; TYPE_1__* profile; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int max_state; int /*<<< orphan*/ * freq_table; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*) ; 
 struct devfreq* to_devfreq (struct device*) ; 

__attribute__((used)) static ssize_t available_frequencies_show(struct device *d,
					  struct device_attribute *attr,
					  char *buf)
{
	struct devfreq *df = to_devfreq(d);
	ssize_t count = 0;
	int i;

	mutex_lock(&df->lock);

	for (i = 0; i < df->profile->max_state; i++)
		count += scnprintf(&buf[count], (PAGE_SIZE - count - 2),
				"%lu ", df->profile->freq_table[i]);

	mutex_unlock(&df->lock);
	/* Truncate the trailing space */
	if (count)
		count--;

	count += sprintf(&buf[count], "\n");

	return count;
}