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
struct appldata_ops {int /*<<< orphan*/  ctl_table; int /*<<< orphan*/  sysctl_header; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  appldata_ops_mutex ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ ) ; 

void appldata_unregister_ops(struct appldata_ops *ops)
{
	mutex_lock(&appldata_ops_mutex);
	list_del(&ops->list);
	mutex_unlock(&appldata_ops_mutex);
	unregister_sysctl_table(ops->sysctl_header);
	kfree(ops->ctl_table);
}