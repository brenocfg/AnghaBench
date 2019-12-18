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
struct oexport_args {int dummy; } ;
struct export_args {scalar_t__ ex_numsecflavors; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (struct oexport_args const*,struct export_args*,int) ; 

void
vfs_oexport_conv(const struct oexport_args *oexp, struct export_args *exp)
{

	bcopy(oexp, exp, sizeof(*oexp));
	exp->ex_numsecflavors = 0;
}