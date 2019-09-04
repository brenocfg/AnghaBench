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
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int REV_SHIFT ; 

__attribute__((used)) static int omit_in_dense(struct commit *commit, struct commit **rev, int n)
{
	/* If the commit is tip of the named branches, do not
	 * omit it.
	 * Otherwise, if it is a merge that is reachable from only one
	 * tip, it is not that interesting.
	 */
	int i, flag, count;
	for (i = 0; i < n; i++)
		if (rev[i] == commit)
			return 0;
	flag = commit->object.flags;
	for (i = count = 0; i < n; i++) {
		if (flag & (1u << (i + REV_SHIFT)))
			count++;
	}
	if (count == 1)
		return 1;
	return 0;
}