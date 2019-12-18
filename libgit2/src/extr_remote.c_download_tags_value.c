#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  download_tags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_7__ {scalar_t__ value; } ;
typedef  TYPE_2__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_ALL ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_NONE ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int git_config__lookup_entry (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int download_tags_value(git_remote *remote, git_config *cfg)
{
	git_config_entry *ce;
	git_buf buf = GIT_BUF_INIT;
	int error;

	if (git_buf_printf(&buf, "remote.%s.tagopt", remote->name) < 0)
		return -1;

	error = git_config__lookup_entry(&ce, cfg, git_buf_cstr(&buf), false);
	git_buf_dispose(&buf);

	if (!error && ce && ce->value) {
		if (!strcmp(ce->value, "--no-tags"))
			remote->download_tags = GIT_REMOTE_DOWNLOAD_TAGS_NONE;
		else if (!strcmp(ce->value, "--tags"))
			remote->download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;
	}

	git_config_entry_free(ce);
	return error;
}