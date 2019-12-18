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
struct TYPE_4__ {int nr; struct commit** list; } ;
struct write_commit_graph_context {int /*<<< orphan*/  progress_cnt; int /*<<< orphan*/  progress; TYPE_1__ commits; } ;
struct hashfile {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  hash; } ;
struct TYPE_5__ {TYPE_3__ oid; } ;
struct commit {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite (struct hashfile*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_graph_chunk_oids(struct hashfile *f, int hash_len,
				   struct write_commit_graph_context *ctx)
{
	struct commit **list = ctx->commits.list;
	int count;
	for (count = 0; count < ctx->commits.nr; count++, list++) {
		display_progress(ctx->progress, ++ctx->progress_cnt);
		hashwrite(f, (*list)->object.oid.hash, (int)hash_len);
	}
}