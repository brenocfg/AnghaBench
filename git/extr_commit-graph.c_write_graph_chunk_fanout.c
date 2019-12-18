#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr; struct commit** list; } ;
struct write_commit_graph_context {int /*<<< orphan*/  progress_cnt; int /*<<< orphan*/  progress; TYPE_3__ commits; } ;
struct hashfile {int dummy; } ;
struct TYPE_4__ {int* hash; } ;
struct TYPE_5__ {TYPE_1__ oid; } ;
struct commit {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite_be32 (struct hashfile*,int) ; 

__attribute__((used)) static void write_graph_chunk_fanout(struct hashfile *f,
				     struct write_commit_graph_context *ctx)
{
	int i, count = 0;
	struct commit **list = ctx->commits.list;

	/*
	 * Write the first-level table (the list is sorted,
	 * but we use a 256-entry lookup to be able to avoid
	 * having to do eight extra binary search iterations).
	 */
	for (i = 0; i < 256; i++) {
		while (count < ctx->commits.nr) {
			if ((*list)->object.oid.hash[0] != i)
				break;
			display_progress(ctx->progress, ++ctx->progress_cnt);
			count++;
			list++;
		}

		hashwrite_be32(f, count);
	}
}