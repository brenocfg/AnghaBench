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
typedef  int uint32_t ;
struct TYPE_5__ {int nr; int /*<<< orphan*/ * list; int /*<<< orphan*/  alloc; } ;
struct write_commit_graph_context {int /*<<< orphan*/  progress; scalar_t__ check_oids; TYPE_2__ oids; int /*<<< orphan*/  r; scalar_t__ report_progress; } ;
struct string_list {int nr; TYPE_3__* items; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_oid_hex (int /*<<< orphan*/ ,struct object_id*,char const**) ; 
 int /*<<< orphan*/  start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int fill_oids_from_commit_hex(struct write_commit_graph_context *ctx,
				     struct string_list *commit_hex)
{
	uint32_t i;
	struct strbuf progress_title = STRBUF_INIT;

	if (ctx->report_progress) {
		strbuf_addf(&progress_title,
			    Q_("Finding commits for commit graph from %d ref",
			       "Finding commits for commit graph from %d refs",
			       commit_hex->nr),
			    commit_hex->nr);
		ctx->progress = start_delayed_progress(
					progress_title.buf,
					commit_hex->nr);
	}
	for (i = 0; i < commit_hex->nr; i++) {
		const char *end;
		struct object_id oid;
		struct commit *result;

		display_progress(ctx->progress, i + 1);
		if (!parse_oid_hex(commit_hex->items[i].string, &oid, &end) &&
		    (result = lookup_commit_reference_gently(ctx->r, &oid, 1))) {
			ALLOC_GROW(ctx->oids.list, ctx->oids.nr + 1, ctx->oids.alloc);
			oidcpy(&ctx->oids.list[ctx->oids.nr], &(result->object.oid));
			ctx->oids.nr++;
		} else if (ctx->check_oids) {
			error(_("invalid commit object id: %s"),
			    commit_hex->items[i].string);
			return -1;
		}
	}
	stop_progress(&ctx->progress);
	strbuf_release(&progress_title);

	return 0;
}