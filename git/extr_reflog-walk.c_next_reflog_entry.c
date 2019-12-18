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
struct reflog_walk_info {size_t nr; struct commit_reflog* last_commit_reflog; struct commit_reflog** logs; } ;
struct commit_reflog {int /*<<< orphan*/  recno; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ log_timestamp (struct commit_reflog*) ; 
 struct commit* next_reflog_commit (struct commit_reflog*) ; 

struct commit *next_reflog_entry(struct reflog_walk_info *walk)
{
	struct commit_reflog *best = NULL;
	struct commit *best_commit = NULL;
	size_t i;

	for (i = 0; i < walk->nr; i++) {
		struct commit_reflog *log = walk->logs[i];
		struct commit *commit = next_reflog_commit(log);

		if (!commit)
			continue;

		if (!best || log_timestamp(log) > log_timestamp(best)) {
			best = log;
			best_commit = commit;
		}
	}

	if (best) {
		best->recno--;
		walk->last_commit_reflog = best;
		return best_commit;
	}

	return NULL;
}