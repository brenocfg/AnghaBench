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
typedef  int /*<<< orphan*/  vnode_t ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_VFS_MOUNT ; 
 int priv_check_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
secpolicy_fs_mount(cred_t *cr, vnode_t *mvp, struct mount *vfsp)
{

	return (priv_check_cred(cr, PRIV_VFS_MOUNT));
}