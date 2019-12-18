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
struct mount {TYPE_1__* mnt_op; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vfs_susp_clean; } ;

/* Variables and functions */

__attribute__((used)) static bool
vn_suspendable(struct mount *mp)
{

	return (mp->mnt_op->vfs_susp_clean != NULL);
}