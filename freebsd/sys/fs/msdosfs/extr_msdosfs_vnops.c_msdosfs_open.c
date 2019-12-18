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
struct vop_open_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_vp; } ;
struct denode {int /*<<< orphan*/  de_FileSize; } ;

/* Variables and functions */
 struct denode* VTODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_create_vobject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msdosfs_open(struct vop_open_args *ap)
{
	struct denode *dep = VTODE(ap->a_vp);
	vnode_create_vobject(ap->a_vp, dep->de_FileSize, ap->a_td);
	return 0;
}