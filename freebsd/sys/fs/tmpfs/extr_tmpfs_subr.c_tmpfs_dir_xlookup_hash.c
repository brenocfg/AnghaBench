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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  tn_dirhead; } ;
struct tmpfs_node {TYPE_1__ tn_dir; } ;
struct tmpfs_dirent {int /*<<< orphan*/  td_hash; } ;

/* Variables and functions */
 struct tmpfs_dirent* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  tmpfs_dir ; 

__attribute__((used)) static struct tmpfs_dirent *
tmpfs_dir_xlookup_hash(struct tmpfs_node *dnode, uint32_t hash)
{
	struct tmpfs_dirent *de, dekey;

	dekey.td_hash = hash;
	de = RB_FIND(tmpfs_dir, &dnode->tn_dir.tn_dirhead, &dekey);
	return (de);
}