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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int nr; int /*<<< orphan*/ * list; int /*<<< orphan*/  alloc; } ;
struct write_commit_graph_context {TYPE_1__ oids; int /*<<< orphan*/  r; int /*<<< orphan*/  progress_done; scalar_t__ progress; } ;
struct packed_git {int dummy; } ;
struct object_info {int* typep; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct object_info OBJECT_INFO_INIT ; 
 int OBJ_COMMIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nth_packed_object_offset (struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 scalar_t__ packed_object_info (int /*<<< orphan*/ ,struct packed_git*,int /*<<< orphan*/ ,struct object_info*) ; 

__attribute__((used)) static int add_packed_commits(const struct object_id *oid,
			      struct packed_git *pack,
			      uint32_t pos,
			      void *data)
{
	struct write_commit_graph_context *ctx = (struct write_commit_graph_context*)data;
	enum object_type type;
	off_t offset = nth_packed_object_offset(pack, pos);
	struct object_info oi = OBJECT_INFO_INIT;

	if (ctx->progress)
		display_progress(ctx->progress, ++ctx->progress_done);

	oi.typep = &type;
	if (packed_object_info(ctx->r, pack, offset, &oi) < 0)
		die(_("unable to get type of object %s"), oid_to_hex(oid));

	if (type != OBJ_COMMIT)
		return 0;

	ALLOC_GROW(ctx->oids.list, ctx->oids.nr + 1, ctx->oids.alloc);
	oidcpy(&(ctx->oids.list[ctx->oids.nr]), oid);
	ctx->oids.nr++;

	return 0;
}