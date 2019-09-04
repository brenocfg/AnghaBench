#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  opts; int /*<<< orphan*/  parse_ctx; } ;
typedef  TYPE_1__ git_patch_parse_ctx ;
typedef  int /*<<< orphan*/  const git_patch_options ;

/* Variables and functions */
 int /*<<< orphan*/  const GIT_PATCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 scalar_t__ git_parse_ctx_init (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

git_patch_parse_ctx *git_patch_parse_ctx_init(
	const char *content,
	size_t content_len,
	const git_patch_options *opts)
{
	git_patch_parse_ctx *ctx;
	git_patch_options default_opts = GIT_PATCH_OPTIONS_INIT;

	if ((ctx = git__calloc(1, sizeof(git_patch_parse_ctx))) == NULL)
		return NULL;

	if ((git_parse_ctx_init(&ctx->parse_ctx, content, content_len)) < 0) {
		git__free(ctx);
		return NULL;
	}

	if (opts)
		memcpy(&ctx->opts, opts, sizeof(git_patch_options));
	else
		memcpy(&ctx->opts, &default_opts, sizeof(git_patch_options));

	GIT_REFCOUNT_INC(ctx);
	return ctx;
}