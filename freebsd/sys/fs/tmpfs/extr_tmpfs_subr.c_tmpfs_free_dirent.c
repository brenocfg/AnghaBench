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
struct tmpfs_node {scalar_t__ tn_links; } ;
struct tmpfs_mount {int /*<<< orphan*/  tm_dirent_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/ * td_name; } ;
struct tmpfs_dirent {TYPE_1__ ud; struct tmpfs_node* td_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TMPFSNAME ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmpfs_dirent_duphead (struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct tmpfs_dirent*) ; 

void
tmpfs_free_dirent(struct tmpfs_mount *tmp, struct tmpfs_dirent *de)
{
	struct tmpfs_node *node;

	node = de->td_node;
	if (node != NULL) {
		MPASS(node->tn_links > 0);
		node->tn_links--;
	}
	if (!tmpfs_dirent_duphead(de) && de->ud.td_name != NULL)
		free(de->ud.td_name, M_TMPFSNAME);
	uma_zfree(tmp->tm_dirent_pool, de);
}