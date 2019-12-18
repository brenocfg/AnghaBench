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
struct vop_getpages_async_args {int /*<<< orphan*/  a_count; int /*<<< orphan*/  a_m; int /*<<< orphan*/  a_arg; int /*<<< orphan*/  (* a_iodone ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  a_rahead; int /*<<< orphan*/  a_rbehind; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int VOP_GETPAGES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vop_stdgetpages_async(struct vop_getpages_async_args *ap)
{
	int error;

	error = VOP_GETPAGES(ap->a_vp, ap->a_m, ap->a_count, ap->a_rbehind,
	    ap->a_rahead);
	ap->a_iodone(ap->a_arg, ap->a_m, ap->a_count, error);
	return (error);
}