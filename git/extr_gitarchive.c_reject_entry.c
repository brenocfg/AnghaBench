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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct path_exists_context {int /*<<< orphan*/  pathspec; TYPE_2__* args; } ;
struct object_id {int dummy; } ;
struct TYPE_4__ {TYPE_1__* repo; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int READ_TREE_RECURSIVE ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (unsigned int) ; 
 int /*<<< orphan*/  match_pathspec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int reject_entry(const struct object_id *oid, struct strbuf *base,
			const char *filename, unsigned mode,
			int stage, void *context)
{
	int ret = -1;
	struct path_exists_context *ctx = context;

	if (S_ISDIR(mode)) {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addbuf(&sb, base);
		strbuf_addstr(&sb, filename);
		if (!match_pathspec(ctx->args->repo->index,
				    &ctx->pathspec,
				    sb.buf, sb.len, 0, NULL, 1))
			ret = READ_TREE_RECURSIVE;
		strbuf_release(&sb);
	}
	return ret;
}