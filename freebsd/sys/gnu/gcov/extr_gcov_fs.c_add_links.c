#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gcov_node {char* links; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {scalar_t__ ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GCOV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 char* basename (char*) ; 
 char debugfs_create_symlink (int /*<<< orphan*/ ,struct dentry*,char*) ; 
 int /*<<< orphan*/  debugfs_remove (char) ; 
 int /*<<< orphan*/  deskew (char const*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_info_filename (int /*<<< orphan*/ ) ; 
 TYPE_1__* gcov_link ; 
 char* get_link_target (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_node_info (struct gcov_node*) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
add_links(struct gcov_node *node, struct dentry *parent)
{
	const char *path_basename;
	char *target;
	int num;
	int i;

	for (num = 0; gcov_link[num].ext; num++)
		/* Nothing. */;
	node->links = malloc((num*sizeof(struct dentry *)), M_GCOV, M_NOWAIT|M_ZERO);
	if (node->links == NULL)
		return;
	for (i = 0; i < num; i++) {
		target = get_link_target(
				gcov_info_filename(get_node_info(node)),
				&gcov_link[i]);
		if (target == NULL)
			goto out_err;
		path_basename = basename(target);
		if (path_basename == target)
			goto out_err;
		node->links[i] = debugfs_create_symlink(deskew(path_basename),
							parent,	target);
		if (!node->links[i])
			goto out_err;
		free(target, M_GCOV);
	}

	return;
out_err:
	free(target, M_GCOV);
	while (i-- > 0)
		debugfs_remove(node->links[i]);
	free(node->links, M_GCOV);
	node->links = NULL;
}