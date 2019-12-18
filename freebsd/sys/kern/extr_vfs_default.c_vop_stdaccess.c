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
struct vop_access_args {int a_accmode; int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VADMIN ; 
 int VAPPEND ; 
 int VEXEC ; 
 int VOP_ACCESSX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VREAD ; 
 int VWRITE ; 

int
vop_stdaccess(struct vop_access_args *ap)
{

	KASSERT((ap->a_accmode & ~(VEXEC | VWRITE | VREAD | VADMIN |
	    VAPPEND)) == 0, ("invalid bit in accmode"));

	return (VOP_ACCESSX(ap->a_vp, ap->a_accmode, ap->a_cred, ap->a_td));
}