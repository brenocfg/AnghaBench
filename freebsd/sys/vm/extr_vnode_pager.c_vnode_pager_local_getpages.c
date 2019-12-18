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
struct vop_getpages_args {int /*<<< orphan*/  a_rahead; int /*<<< orphan*/  a_rbehind; int /*<<< orphan*/  a_count; int /*<<< orphan*/  a_m; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int vnode_pager_generic_getpages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
vnode_pager_local_getpages(struct vop_getpages_args *ap)
{

	return (vnode_pager_generic_getpages(ap->a_vp, ap->a_m, ap->a_count,
	    ap->a_rbehind, ap->a_rahead, NULL, NULL));
}