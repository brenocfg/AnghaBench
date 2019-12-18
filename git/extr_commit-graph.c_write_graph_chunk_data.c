#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int nr; struct commit** list; } ;
struct write_commit_graph_context {int /*<<< orphan*/  new_base_graph; scalar_t__ new_num_commits_in_base; TYPE_1__ commits; int /*<<< orphan*/  progress_cnt; int /*<<< orphan*/  progress; } ;
struct object_id {int* hash; } ;
struct hashfile {int dummy; } ;
struct commit_list {struct commit_list* next; TYPE_5__* item; } ;
struct TYPE_9__ {int /*<<< orphan*/  hash; } ;
struct TYPE_8__ {TYPE_4__ oid; } ;
struct commit {int date; int generation; TYPE_3__ object; struct commit_list* parents; } ;
struct TYPE_7__ {TYPE_4__ oid; } ;
struct TYPE_10__ {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GRAPH_EXTRA_EDGES_NEEDED ; 
 int GRAPH_PARENT_NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_to_sha1 ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_commit_in_graph (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 struct object_id* get_commit_tree_oid (struct commit*) ; 
 int /*<<< orphan*/  hashwrite (struct hashfile*,int*,int) ; 
 int /*<<< orphan*/  hashwrite_be32 (struct hashfile*,int) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  oid_to_hex (TYPE_4__*) ; 
 scalar_t__ parse_commit_no_graph (struct commit*) ; 
 int sha1_pos (int /*<<< orphan*/ ,struct commit**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_graph_chunk_data(struct hashfile *f, int hash_len,
				   struct write_commit_graph_context *ctx)
{
	struct commit **list = ctx->commits.list;
	struct commit **last = ctx->commits.list + ctx->commits.nr;
	uint32_t num_extra_edges = 0;

	while (list < last) {
		struct commit_list *parent;
		struct object_id *tree;
		int edge_value;
		uint32_t packedDate[2];
		display_progress(ctx->progress, ++ctx->progress_cnt);

		if (parse_commit_no_graph(*list))
			die(_("unable to parse commit %s"),
				oid_to_hex(&(*list)->object.oid));
		tree = get_commit_tree_oid(*list);
		if (!tree)
			die(_("unable to get tree for %s"),
				oid_to_hex(&(*list)->object.oid));
		hashwrite(f, tree->hash, hash_len);

		parent = (*list)->parents;

		if (!parent)
			edge_value = GRAPH_PARENT_NONE;
		else {
			edge_value = sha1_pos(parent->item->object.oid.hash,
					      ctx->commits.list,
					      ctx->commits.nr,
					      commit_to_sha1);

			if (edge_value >= 0)
				edge_value += ctx->new_num_commits_in_base;
			else {
				uint32_t pos;
				if (find_commit_in_graph(parent->item,
							 ctx->new_base_graph,
							 &pos))
					edge_value = pos;
			}

			if (edge_value < 0)
				BUG("missing parent %s for commit %s",
				    oid_to_hex(&parent->item->object.oid),
				    oid_to_hex(&(*list)->object.oid));
		}

		hashwrite_be32(f, edge_value);

		if (parent)
			parent = parent->next;

		if (!parent)
			edge_value = GRAPH_PARENT_NONE;
		else if (parent->next)
			edge_value = GRAPH_EXTRA_EDGES_NEEDED | num_extra_edges;
		else {
			edge_value = sha1_pos(parent->item->object.oid.hash,
					      ctx->commits.list,
					      ctx->commits.nr,
					      commit_to_sha1);

			if (edge_value >= 0)
				edge_value += ctx->new_num_commits_in_base;
			else {
				uint32_t pos;
				if (find_commit_in_graph(parent->item,
							 ctx->new_base_graph,
							 &pos))
					edge_value = pos;
			}

			if (edge_value < 0)
				BUG("missing parent %s for commit %s",
				    oid_to_hex(&parent->item->object.oid),
				    oid_to_hex(&(*list)->object.oid));
		}

		hashwrite_be32(f, edge_value);

		if (edge_value & GRAPH_EXTRA_EDGES_NEEDED) {
			do {
				num_extra_edges++;
				parent = parent->next;
			} while (parent);
		}

		if (sizeof((*list)->date) > 4)
			packedDate[0] = htonl(((*list)->date >> 32) & 0x3);
		else
			packedDate[0] = 0;

		packedDate[0] |= htonl((*list)->generation << 2);

		packedDate[1] = htonl((*list)->date);
		hashwrite(f, packedDate, 8);

		list++;
	}
}