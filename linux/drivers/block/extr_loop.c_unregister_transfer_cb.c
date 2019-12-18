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
struct loop_func_table {int dummy; } ;
struct loop_device {struct loop_func_table* lo_encryption; } ;

/* Variables and functions */
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int /*<<< orphan*/  loop_release_xfer (struct loop_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unregister_transfer_cb(int id, void *ptr, void *data)
{
	struct loop_device *lo = ptr;
	struct loop_func_table *xfer = data;

	mutex_lock(&loop_ctl_mutex);
	if (lo->lo_encryption == xfer)
		loop_release_xfer(lo);
	mutex_unlock(&loop_ctl_mutex);
	return 0;
}