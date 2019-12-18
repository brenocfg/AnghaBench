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
struct TYPE_2__ {int /*<<< orphan*/  k_lock; int /*<<< orphan*/  k_list; } ;
struct attribute_container {TYPE_1__ containers; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  attribute_container_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
attribute_container_unregister(struct attribute_container *cont)
{
	int retval = -EBUSY;

	mutex_lock(&attribute_container_mutex);
	spin_lock(&cont->containers.k_lock);
	if (!list_empty(&cont->containers.k_list))
		goto out;
	retval = 0;
	list_del(&cont->node);
 out:
	spin_unlock(&cont->containers.k_lock);
	mutex_unlock(&attribute_container_mutex);
	return retval;

}