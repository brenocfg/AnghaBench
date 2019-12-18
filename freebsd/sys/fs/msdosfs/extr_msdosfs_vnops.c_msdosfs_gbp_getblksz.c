#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_4__ {TYPE_1__* de_pmp; } ;
struct TYPE_3__ {int pm_bpcluster; } ;

/* Variables and functions */
 TYPE_2__* VTODE (struct vnode*) ; 

__attribute__((used)) static int
msdosfs_gbp_getblksz(struct vnode *vp, daddr_t lbn)
{

	return (VTODE(vp)->de_pmp->pm_bpcluster);
}