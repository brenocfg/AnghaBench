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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ vn_matchops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsctl_ops_root ; 
 int /*<<< orphan*/  zfsctl_ops_shares_dir ; 
 int /*<<< orphan*/  zfsctl_ops_snapdir ; 
 int /*<<< orphan*/  zfsctl_ops_snapshot ; 

boolean_t
zfsctl_is_node(vnode_t *vp)
{
	return (vn_matchops(vp, zfsctl_ops_root) ||
	    vn_matchops(vp, zfsctl_ops_snapdir) ||
	    vn_matchops(vp, zfsctl_ops_snapshot) ||
	    vn_matchops(vp, zfsctl_ops_shares_dir));

}