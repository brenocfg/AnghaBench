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
struct seq_file {int /*<<< orphan*/  private; } ;
struct gcov_node {scalar_t__ num_loaded; } ;
struct gcov_info {int dummy; } ;
struct file {struct seq_file* private_data; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_reset (struct gcov_info*) ; 
 struct gcov_info* gcov_iter_get_info (int /*<<< orphan*/ ) ; 
 struct gcov_node* get_node_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_lock ; 
 int /*<<< orphan*/  remove_node (struct gcov_node*) ; 
 int /*<<< orphan*/  reset_node (struct gcov_node*) ; 

__attribute__((used)) static ssize_t
gcov_seq_write(struct file *file, const char *addr, size_t len, off_t *pos)
{
	struct seq_file *seq;
	struct gcov_info *info;
	struct gcov_node *node;

	seq = file->private_data;
	info = gcov_iter_get_info(seq->private);
	mtx_lock(&node_lock);
	node = get_node_by_name(gcov_info_filename(info));
	if (node) {
		/* Reset counts or remove node for unloaded modules. */
		if (node->num_loaded == 0)
			remove_node(node);
		else
			reset_node(node);
	}
	/* Reset counts for open file. */
	gcov_info_reset(info);
	mtx_unlock(&node_lock);

	return (len);
}