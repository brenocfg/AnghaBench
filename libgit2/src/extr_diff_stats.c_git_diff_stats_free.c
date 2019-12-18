#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* filestats; int /*<<< orphan*/  diff; } ;
typedef  TYPE_1__ git_diff_stats ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ ) ; 

void git_diff_stats_free(git_diff_stats *stats)
{
	if (stats == NULL)
		return;

	git_diff_free(stats->diff); /* bumped refcount in constructor */
	git__free(stats->filestats);
	git__free(stats);
}