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
struct vop_reclaim_args {int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  lf_iteratelocks_vnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_cancel_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_reclaim_free_lock ; 

int
nlm_reclaim(struct vop_reclaim_args *ap)
{

	nlm_cancel_wait(ap->a_vp);
	lf_iteratelocks_vnode(ap->a_vp, nlm_reclaim_free_lock, NULL);
	return (0);
}