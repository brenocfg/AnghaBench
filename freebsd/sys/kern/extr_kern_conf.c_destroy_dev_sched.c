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
struct cdev {int dummy; } ;

/* Variables and functions */
 int destroy_dev_sched_cb (struct cdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
destroy_dev_sched(struct cdev *dev)
{

	return (destroy_dev_sched_cb(dev, NULL, NULL));
}