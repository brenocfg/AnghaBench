#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct progress {int dummy; } ;
struct hashfile {int dummy; } ;
struct TYPE_3__ {int* hash; } ;
struct TYPE_4__ {TYPE_1__ oid; } ;
struct commit {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_progress (struct progress*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite_be32 (struct hashfile*,int) ; 

__attribute__((used)) static void write_graph_chunk_fanout(struct hashfile *f,
				     struct commit **commits,
				     int nr_commits,
				     struct progress *progress,
				     uint64_t *progress_cnt)
{
	int i, count = 0;
	struct commit **list = commits;

	/*
	 * Write the first-level table (the list is sorted,
	 * but we use a 256-entry lookup to be able to avoid
	 * having to do eight extra binary search iterations).
	 */
	for (i = 0; i < 256; i++) {
		while (count < nr_commits) {
			if ((*list)->object.oid.hash[0] != i)
				break;
			display_progress(progress, ++*progress_cnt);
			count++;
			list++;
		}

		hashwrite_be32(f, count);
	}
}