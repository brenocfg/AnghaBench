#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct progress {int dummy; } ;
struct hashfile {int dummy; } ;
struct commit_list {struct commit_list* next; TYPE_2__* item; } ;
struct TYPE_8__ {int /*<<< orphan*/  hash; } ;
struct TYPE_7__ {TYPE_4__ oid; } ;
struct commit {TYPE_3__ object; struct commit_list* parents; } ;
struct TYPE_5__ {TYPE_4__ oid; } ;
struct TYPE_6__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GRAPH_LAST_EDGE ; 
 int /*<<< orphan*/  commit_to_sha1 ; 
 int /*<<< orphan*/  display_progress (struct progress*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite_be32 (struct hashfile*,int) ; 
 int /*<<< orphan*/  oid_to_hex (TYPE_4__*) ; 
 int sha1_pos (int /*<<< orphan*/ ,struct commit**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_graph_chunk_extra_edges(struct hashfile *f,
					  struct commit **commits,
					  int nr_commits,
					  struct progress *progress,
					  uint64_t *progress_cnt)
{
	struct commit **list = commits;
	struct commit **last = commits + nr_commits;
	struct commit_list *parent;

	while (list < last) {
		int num_parents = 0;

		display_progress(progress, ++*progress_cnt);

		for (parent = (*list)->parents; num_parents < 3 && parent;
		     parent = parent->next)
			num_parents++;

		if (num_parents <= 2) {
			list++;
			continue;
		}

		/* Since num_parents > 2, this initializer is safe. */
		for (parent = (*list)->parents->next; parent; parent = parent->next) {
			int edge_value = sha1_pos(parent->item->object.oid.hash,
						  commits,
						  nr_commits,
						  commit_to_sha1);

			if (edge_value < 0)
				BUG("missing parent %s for commit %s",
				    oid_to_hex(&parent->item->object.oid),
				    oid_to_hex(&(*list)->object.oid));
			else if (!parent->next)
				edge_value |= GRAPH_LAST_EDGE;

			hashwrite_be32(f, edge_value);
		}

		list++;
	}
}