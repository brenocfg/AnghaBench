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
struct traversal_context {int (* filter_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  show_data; int /*<<< orphan*/  (* show_object ) (struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  filter_data; TYPE_1__* revs; } ;
struct strbuf {size_t len; int /*<<< orphan*/ * buf; } ;
struct object {int flags; int /*<<< orphan*/  oid; } ;
struct blob {struct object object; } ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;
struct TYPE_2__ {int /*<<< orphan*/  repo; scalar_t__ exclude_promisor_objects; int /*<<< orphan*/  blob_objects; } ;

/* Variables and functions */
 int LOFR_DO_SHOW ; 
 int LOFR_MARK_SEEN ; 
 int /*<<< orphan*/  LOFS_BLOB ; 
 int NOT_USER_GIVEN ; 
 int SEEN ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  has_object_file (int /*<<< orphan*/ *) ; 
 scalar_t__ is_promisor_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_blob(struct traversal_context *ctx,
			 struct blob *blob,
			 struct strbuf *path,
			 const char *name)
{
	struct object *obj = &blob->object;
	size_t pathlen;
	enum list_objects_filter_result r = LOFR_MARK_SEEN | LOFR_DO_SHOW;

	if (!ctx->revs->blob_objects)
		return;
	if (!obj)
		die("bad blob object");
	if (obj->flags & (UNINTERESTING | SEEN))
		return;

	/*
	 * Pre-filter known-missing objects when explicitly requested.
	 * Otherwise, a missing object error message may be reported
	 * later (depending on other filtering criteria).
	 *
	 * Note that this "--exclude-promisor-objects" pre-filtering
	 * may cause the actual filter to report an incomplete list
	 * of missing objects.
	 */
	if (ctx->revs->exclude_promisor_objects &&
	    !has_object_file(&obj->oid) &&
	    is_promisor_object(&obj->oid))
		return;

	pathlen = path->len;
	strbuf_addstr(path, name);
	if ((obj->flags & NOT_USER_GIVEN) && ctx->filter_fn)
		r = ctx->filter_fn(ctx->revs->repo,
				   LOFS_BLOB, obj,
				   path->buf, &path->buf[pathlen],
				   ctx->filter_data);
	if (r & LOFR_MARK_SEEN)
		obj->flags |= SEEN;
	if (r & LOFR_DO_SHOW)
		ctx->show_object(obj, path->buf, ctx->show_data);
	strbuf_setlen(path, pathlen);
}