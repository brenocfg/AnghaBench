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
struct tree {int dummy; } ;
struct traversal_context {TYPE_1__* revs; int /*<<< orphan*/  show_data; int /*<<< orphan*/  (* show_object ) (struct object*,char const*,int /*<<< orphan*/ ) ;} ;
struct strbuf {scalar_t__ len; } ;
struct object_array_entry {char* name; char* path; struct object* item; } ;
struct object {int flags; scalar_t__ type; int /*<<< orphan*/  oid; } ;
struct blob {int dummy; } ;
struct TYPE_4__ {int nr; struct object_array_entry* objects; } ;
struct TYPE_3__ {TYPE_2__ pending; } ;

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_TAG ; 
 scalar_t__ OBJ_TREE ; 
 int SEEN ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  object_array_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_blob (struct traversal_context*,struct blob*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  process_tree (struct traversal_context*,struct tree*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  stub1 (struct object*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void traverse_trees_and_blobs(struct traversal_context *ctx,
				     struct strbuf *base)
{
	int i;

	assert(base->len == 0);

	for (i = 0; i < ctx->revs->pending.nr; i++) {
		struct object_array_entry *pending = ctx->revs->pending.objects + i;
		struct object *obj = pending->item;
		const char *name = pending->name;
		const char *path = pending->path;
		if (obj->flags & (UNINTERESTING | SEEN))
			continue;
		if (obj->type == OBJ_TAG) {
			obj->flags |= SEEN;
			ctx->show_object(obj, name, ctx->show_data);
			continue;
		}
		if (!path)
			path = "";
		if (obj->type == OBJ_TREE) {
			process_tree(ctx, (struct tree *)obj, base, path);
			continue;
		}
		if (obj->type == OBJ_BLOB) {
			process_blob(ctx, (struct blob *)obj, base, path);
			continue;
		}
		die("unknown pending object %s (%s)",
		    oid_to_hex(&obj->oid), name);
	}
	object_array_clear(&ctx->revs->pending);
}