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
struct vfsconf {int dummy; } ;
struct mqfs_info {int /*<<< orphan*/  mi_lock; int /*<<< orphan*/ * mi_root; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_tag ; 
 struct mqfs_info mqfs_data ; 
 int /*<<< orphan*/  mqfs_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqfs_fileno_uninit (struct mqfs_info*) ; 
 int /*<<< orphan*/  mqfs_osd_jail_slot ; 
 int /*<<< orphan*/  mqnode_zone ; 
 int /*<<< orphan*/  mqnoti_zone ; 
 int /*<<< orphan*/  mqueue_zone ; 
 int /*<<< orphan*/  mvdata_zone ; 
 int /*<<< orphan*/  osd_jail_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_exit ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unloadable ; 

__attribute__((used)) static int
mqfs_uninit(struct vfsconf *vfc)
{
	struct mqfs_info *mi;

	if (!unloadable)
		return (EOPNOTSUPP);
	osd_jail_deregister(mqfs_osd_jail_slot);
	EVENTHANDLER_DEREGISTER(process_exit, exit_tag);
	mi = &mqfs_data;
	mqfs_destroy(mi->mi_root);
	mi->mi_root = NULL;
	mqfs_fileno_uninit(mi);
	sx_destroy(&mi->mi_lock);
	uma_zdestroy(mqnode_zone);
	uma_zdestroy(mqueue_zone);
	uma_zdestroy(mvdata_zone);
	uma_zdestroy(mqnoti_zone);
	return (0);
}