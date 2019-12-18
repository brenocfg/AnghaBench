#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vop_rmdir_args {int /*<<< orphan*/  a_gen; int /*<<< orphan*/  a_vp; } ;
struct TYPE_2__ {int /*<<< orphan*/  null_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLV_DROP ; 
 TYPE_1__* VTONULL (int /*<<< orphan*/ ) ; 
 int null_bypass (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
null_rmdir(struct vop_rmdir_args *ap)
{

	VTONULL(ap->a_vp)->null_flags |= NULLV_DROP;
	return (null_bypass(&ap->a_gen));
}