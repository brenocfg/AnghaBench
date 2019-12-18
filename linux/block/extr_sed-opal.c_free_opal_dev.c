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
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  kfree (struct opal_dev*) ; 

void free_opal_dev(struct opal_dev *dev)
{
	if (!dev)
		return;

	clean_opal_dev(dev);
	kfree(dev);
}