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
struct vop_generic_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  newnfs_fifoops_nosig ; 
 int vop_sigdefer (int /*<<< orphan*/ *,struct vop_generic_args*) ; 

__attribute__((used)) static int
nfs_fifoops_bypass(struct vop_generic_args *a)
{

	return (vop_sigdefer(&newnfs_fifoops_nosig, a));
}