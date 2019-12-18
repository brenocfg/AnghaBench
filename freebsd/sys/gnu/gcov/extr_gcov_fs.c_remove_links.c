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
struct gcov_node {int /*<<< orphan*/ * links; } ;
struct TYPE_2__ {scalar_t__ ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GCOV ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* gcov_link ; 

__attribute__((used)) static void
remove_links(struct gcov_node *node)
{

	if (node->links == NULL)
		return;
	for (int i = 0; gcov_link[i].ext; i++)
		debugfs_remove(node->links[i]);
	free(node->links, M_GCOV);
	node->links = NULL;
}