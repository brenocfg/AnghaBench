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
struct seq_file {int dummy; } ;
struct file {struct dma_buf* private_data; } ;
struct dma_buf {int /*<<< orphan*/  lock; scalar_t__ name; scalar_t__ exp_name; int /*<<< orphan*/  file; scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ file_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 

__attribute__((used)) static void dma_buf_show_fdinfo(struct seq_file *m, struct file *file)
{
	struct dma_buf *dmabuf = file->private_data;

	seq_printf(m, "size:\t%zu\n", dmabuf->size);
	/* Don't count the temporary reference taken inside procfs seq_show */
	seq_printf(m, "count:\t%ld\n", file_count(dmabuf->file) - 1);
	seq_printf(m, "exp_name:\t%s\n", dmabuf->exp_name);
	mutex_lock(&dmabuf->lock);
	if (dmabuf->name)
		seq_printf(m, "name:\t%s\n", dmabuf->name);
	mutex_unlock(&dmabuf->lock);
}