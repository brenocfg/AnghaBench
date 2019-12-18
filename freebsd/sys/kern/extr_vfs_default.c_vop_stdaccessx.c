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
struct vop_accessx_args {scalar_t__ a_accmode; int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_vp; } ;
typedef  scalar_t__ accmode_t ;

/* Variables and functions */
 int VOP_ACCESS (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_unixify_accmode (scalar_t__*) ; 

int
vop_stdaccessx(struct vop_accessx_args *ap)
{
	int error;
	accmode_t accmode = ap->a_accmode;

	error = vfs_unixify_accmode(&accmode);
	if (error != 0)
		return (error);

	if (accmode == 0)
		return (0);

	return (VOP_ACCESS(ap->a_vp, accmode, ap->a_cred, ap->a_td));
}