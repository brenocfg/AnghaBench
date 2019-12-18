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
struct tmpfs_dirent {scalar_t__ td_hash; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
tmpfs_dirtree_cmp(struct tmpfs_dirent *a, struct tmpfs_dirent *b)
{
	if (a->td_hash > b->td_hash)
		return (1);
	else if (a->td_hash < b->td_hash)
		return (-1);
	return (0);
}