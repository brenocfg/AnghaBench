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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct label {int dummy; } ;
struct devfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_DEVFS ; 
 int /*<<< orphan*/  MAGIC_MOUNT ; 
 int /*<<< orphan*/  MAGIC_VNODE ; 
 int /*<<< orphan*/  devfs_vnode_associate ; 

__attribute__((used)) static void
test_devfs_vnode_associate(struct mount *mp, struct label *mplabel,
    struct devfs_dirent *de, struct label *delabel, struct vnode *vp,
    struct label *vplabel)
{

	LABEL_CHECK(mplabel, MAGIC_MOUNT);
	LABEL_CHECK(delabel, MAGIC_DEVFS);
	LABEL_CHECK(vplabel, MAGIC_VNODE);
	COUNTER_INC(devfs_vnode_associate);
}