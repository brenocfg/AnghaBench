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
struct vop_cachedlookup_args {int /*<<< orphan*/  a_cnp; int /*<<< orphan*/  a_vpp; int /*<<< orphan*/  a_dvp; } ;

/* Variables and functions */
 int tmpfs_lookup1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmpfs_cached_lookup(struct vop_cachedlookup_args *v)
{

	return (tmpfs_lookup1(v->a_dvp, v->a_vpp, v->a_cnp));
}