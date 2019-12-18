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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int nvlist_copy_pairs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvlist_merge(nvlist_t *dst, nvlist_t *nvl, int flag)
{
	if (nvl == NULL || dst == NULL)
		return (EINVAL);

	if (dst != nvl)
		return (nvlist_copy_pairs(nvl, dst));

	return (0);
}