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
struct commit_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 

__attribute__((used)) static int mark_seen(struct commit *commit, struct commit_list **seen_p)
{
	if (!commit->object.flags) {
		commit_list_insert(commit, seen_p);
		return 1;
	}
	return 0;
}