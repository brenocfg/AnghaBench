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
struct write_commit_graph_context {int num_commit_graphs_after; int /*<<< orphan*/  new_base_graph; } ;
struct hashfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int write_graph_chunk_base_1 (struct hashfile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_graph_chunk_base(struct hashfile *f,
				  struct write_commit_graph_context *ctx)
{
	int num = write_graph_chunk_base_1(f, ctx->new_base_graph);

	if (num != ctx->num_commit_graphs_after - 1) {
		error(_("failed to write correct number of base graph ids"));
		return -1;
	}

	return 0;
}