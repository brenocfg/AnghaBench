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
struct gcov_node {int /*<<< orphan*/  children; int /*<<< orphan*/  dentry; int /*<<< orphan*/  name; void* loaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gcov_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  M_GCOV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  add_links (struct gcov_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_entry ; 
 int /*<<< orphan*/  all_head ; 
 int /*<<< orphan*/  children_entry ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct gcov_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deskew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct gcov_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_data_fops ; 
 int /*<<< orphan*/  init_node (struct gcov_node*,struct gcov_info*,char const*,struct gcov_node*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct gcov_node *
new_node(struct gcov_node *parent, struct gcov_info *info, const char *name)
{
	struct gcov_node *node;

	node = malloc(sizeof(struct gcov_node) + strlen(name) + 1, M_GCOV, M_NOWAIT|M_ZERO);
	if (!node)
		goto err_nomem;
	if (info) {
		node->loaded_info = malloc(sizeof(struct gcov_info *), M_GCOV, M_NOWAIT|M_ZERO);
		if (!node->loaded_info)
			goto err_nomem;
	}
	init_node(node, info, name, parent);
	/* Differentiate between gcov data file nodes and directory nodes. */
	if (info) {
		node->dentry = debugfs_create_file(deskew(node->name), 0600,
					parent->dentry, node, &gcov_data_fops);
	} else
		node->dentry = debugfs_create_dir(node->name, parent->dentry);
	if (!node->dentry) {
		log(LOG_WARNING, "could not create file\n");
		free(node, M_GCOV);
		return NULL;
	}
	if (info)
		add_links(node, parent->dentry);
	LIST_INSERT_HEAD(&parent->children, node, children_entry);
	LIST_INSERT_HEAD(&all_head, node, all_entry);

	return (node);

err_nomem:
	free(node, M_GCOV);
	log(LOG_WARNING, "out of memory\n");
	return NULL;
}