#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int started; int ended; int /*<<< orphan*/  flags; scalar_t__ pathlist_walk_idx; scalar_t__ stat_calls; } ;
typedef  TYPE_1__ git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_FIRST_ACCESS ; 

__attribute__((used)) static void iterator_clear(git_iterator *iter)
{
	iter->started = false;
	iter->ended = false;
	iter->stat_calls = 0;
	iter->pathlist_walk_idx = 0;
	iter->flags &= ~GIT_ITERATOR_FIRST_ACCESS;
}