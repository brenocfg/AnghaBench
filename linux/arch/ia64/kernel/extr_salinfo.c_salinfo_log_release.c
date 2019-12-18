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
struct salinfo_data {scalar_t__ state; scalar_t__ open; int /*<<< orphan*/ * oemdata; int /*<<< orphan*/ * log_buffer; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct salinfo_data* PDE_DATA (struct inode*) ; 
 scalar_t__ STATE_NO_DATA ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
salinfo_log_release(struct inode *inode, struct file *file)
{
	struct salinfo_data *data = PDE_DATA(inode);

	if (data->state == STATE_NO_DATA) {
		vfree(data->log_buffer);
		vfree(data->oemdata);
		data->log_buffer = NULL;
		data->oemdata = NULL;
	}
	spin_lock(&data_lock);
	data->open = 0;
	spin_unlock(&data_lock);
	return 0;
}