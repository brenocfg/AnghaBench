#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ rewrite_notes_ref; } ;
typedef  TYPE_1__ git_rebase_options ;
struct TYPE_13__ {TYPE_2__* rewrite_notes_ref; } ;
struct TYPE_12__ {TYPE_5__ options; } ;
typedef  TYPE_2__ git_rebase ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_REBASE_OPTIONS_VERSION ; 
 TYPE_2__* git__calloc (int,int) ; 
 TYPE_2__* git__strdup (scalar_t__) ; 
 int /*<<< orphan*/  git_rebase_options_init (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_1__ const*,int) ; 

__attribute__((used)) static int rebase_alloc(git_rebase **out, const git_rebase_options *rebase_opts)
{
	git_rebase *rebase = git__calloc(1, sizeof(git_rebase));
	GIT_ERROR_CHECK_ALLOC(rebase);

	*out = NULL;

	if (rebase_opts)
		memcpy(&rebase->options, rebase_opts, sizeof(git_rebase_options));
	else
		git_rebase_options_init(&rebase->options, GIT_REBASE_OPTIONS_VERSION);

	if (rebase_opts && rebase_opts->rewrite_notes_ref) {
		rebase->options.rewrite_notes_ref = git__strdup(rebase_opts->rewrite_notes_ref);
		GIT_ERROR_CHECK_ALLOC(rebase->options.rewrite_notes_ref);
	}

	*out = rebase;

	return 0;
}