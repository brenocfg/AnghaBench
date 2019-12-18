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
struct gcov_node {struct gcov_node* parent; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GCOV ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 struct gcov_node* get_child_by_name (struct gcov_node*,char*) ; 
 struct gcov_node* new_node (struct gcov_node*,struct gcov_info*,char*) ; 
 int /*<<< orphan*/  remove_node (struct gcov_node*) ; 
 struct gcov_node root_node ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_node(struct gcov_info *info)
{
	char *filename;
	char *curr;
	char *next;
	struct gcov_node *parent;
	struct gcov_node *node;

	filename = strdup_flags(gcov_info_filename(info), M_GCOV, M_NOWAIT);
	if (filename == NULL)
		return;
	parent = &root_node;
	/* Create directory nodes along the path. */
	for (curr = filename; (next = strchr(curr, '/')); curr = next + 1) {
		if (curr == next)
			continue;
		*next = 0;
		if (strcmp(curr, ".") == 0)
			continue;
		if (strcmp(curr, "..") == 0) {
			if (!parent->parent)
				goto err_remove;
			parent = parent->parent;
			continue;
		}
		node = get_child_by_name(parent, curr);
		if (!node) {
			node = new_node(parent, NULL, curr);
			if (!node)
				goto err_remove;
		}
		parent = node;
	}
	/* Create file node. */
	node = new_node(parent, info, curr);
	if (!node)
		goto err_remove;
out:
	free(filename, M_GCOV);
	return;

err_remove:
	remove_node(parent);
	goto out;
}