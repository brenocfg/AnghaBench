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
struct vnode {TYPE_2__* v_mount; } ;
struct inode {scalar_t__ i_number; int /*<<< orphan*/  i_effnlink; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_3__ {int /*<<< orphan*/  f_mntonname; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  uprintf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_bad_link_count(const char *funcname, struct vnode *dvp)
{
	struct inode *dip;

	dip = VTOI(dvp);
	uprintf("%s: Bad link count %d on parent inode %jd in file system %s\n",
	    funcname, dip->i_effnlink, (intmax_t)dip->i_number,
	    dvp->v_mount->mnt_stat.f_mntonname);
}