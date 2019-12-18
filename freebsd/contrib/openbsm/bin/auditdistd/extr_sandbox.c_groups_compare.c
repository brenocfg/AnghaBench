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
typedef  scalar_t__ gid_t ;

/* Variables and functions */

__attribute__((used)) static int
groups_compare(const void *grp0, const void *grp1)
{
	gid_t gr0 = *(const gid_t *)grp0;
	gid_t gr1 = *(const gid_t *)grp1;

	return (gr0 <= gr1 ? (gr0 < gr1 ? -1 : 0) : 1);

}