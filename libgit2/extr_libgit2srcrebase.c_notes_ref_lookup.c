#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rewrite_notes_ref; } ;
struct TYPE_5__ {int /*<<< orphan*/  repo; TYPE_1__ options; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git_buf_attach_notowned (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static int notes_ref_lookup(git_buf *out, git_rebase *rebase)
{
	git_config *config = NULL;
	int do_rewrite, error;

	if (rebase->options.rewrite_notes_ref) {
		git_buf_attach_notowned(out,
			rebase->options.rewrite_notes_ref,
			strlen(rebase->options.rewrite_notes_ref));
		return 0;
	}

	if ((error = git_repository_config(&config, rebase->repo)) < 0 ||
		(error = git_config_get_bool(&do_rewrite, config, "notes.rewrite.rebase")) < 0) {

		if (error != GIT_ENOTFOUND)
			goto done;

		git_error_clear();
		do_rewrite = 1;
	}

	error = do_rewrite ?
		git_config_get_string_buf(out, config, "notes.rewriteref") :
		GIT_ENOTFOUND;

done:
	git_config_free(config);
	return error;
}