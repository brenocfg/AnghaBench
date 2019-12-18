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
struct vop_copy_file_range_args {int /*<<< orphan*/  a_fsizetd; int /*<<< orphan*/  a_outcred; int /*<<< orphan*/  a_incred; int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_lenp; int /*<<< orphan*/  a_outoffp; int /*<<< orphan*/  a_outvp; int /*<<< orphan*/  a_inoffp; int /*<<< orphan*/  a_invp; } ;

/* Variables and functions */
 int vn_generic_copy_file_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vop_stdcopy_file_range(struct vop_copy_file_range_args *ap)
{
	int error;

	error = vn_generic_copy_file_range(ap->a_invp, ap->a_inoffp,
	    ap->a_outvp, ap->a_outoffp, ap->a_lenp, ap->a_flags, ap->a_incred,
	    ap->a_outcred, ap->a_fsizetd);
	return (error);
}