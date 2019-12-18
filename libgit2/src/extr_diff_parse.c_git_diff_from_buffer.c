#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  deltas; } ;
struct TYPE_15__ {scalar_t__ remain_len; } ;
struct TYPE_16__ {TYPE_5__ base; int /*<<< orphan*/  patches; TYPE_1__ parse_ctx; } ;
typedef  TYPE_2__ git_patch_parse_ctx ;
struct TYPE_17__ {struct TYPE_17__* delta; } ;
typedef  TYPE_3__ git_patch ;
typedef  TYPE_2__ git_diff_parsed ;
typedef  TYPE_5__ git_diff ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 TYPE_2__* diff_parsed_alloc () ; 
 int /*<<< orphan*/  git_diff_free (TYPE_5__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_patch_parse (TYPE_3__**,TYPE_2__*) ; 
 int /*<<< orphan*/  git_patch_parse_ctx_free (TYPE_2__*) ; 
 TYPE_2__* git_patch_parse_ctx_init (char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ git_vector_length (int /*<<< orphan*/ *) ; 

int git_diff_from_buffer(
	git_diff **out,
	const char *content,
	size_t content_len)
{
	git_diff_parsed *diff;
	git_patch *patch;
	git_patch_parse_ctx *ctx = NULL;
	int error = 0;

	*out = NULL;

	diff = diff_parsed_alloc();
	GIT_ERROR_CHECK_ALLOC(diff);

	ctx = git_patch_parse_ctx_init(content, content_len, NULL);
	GIT_ERROR_CHECK_ALLOC(ctx);

	while (ctx->parse_ctx.remain_len) {
		if ((error = git_patch_parse(&patch, ctx)) < 0)
			break;

		git_vector_insert(&diff->patches, patch);
		git_vector_insert(&diff->base.deltas, patch->delta);
	}

	if (error == GIT_ENOTFOUND && git_vector_length(&diff->patches) > 0) {
		git_error_clear();
		error = 0;
	}

	git_patch_parse_ctx_free(ctx);

	if (error < 0)
		git_diff_free(&diff->base);
	else
		*out = &diff->base;

	return error;
}