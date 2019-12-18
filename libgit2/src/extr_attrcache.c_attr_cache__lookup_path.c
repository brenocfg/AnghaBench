#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 char* git__strdup (char const*) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_config__lookup_entry (TYPE_1__**,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int git_sysdir_expand_global_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_sysdir_find_xdg_file (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int attr_cache__lookup_path(
	char **out, git_config *cfg, const char *key, const char *fallback)
{
	git_buf buf = GIT_BUF_INIT;
	int error;
	git_config_entry *entry = NULL;

	*out = NULL;

	if ((error = git_config__lookup_entry(&entry, cfg, key, false)) < 0)
		return error;

	if (entry) {
		const char *cfgval = entry->value;

		/* expand leading ~/ as needed */
		if (cfgval && cfgval[0] == '~' && cfgval[1] == '/') {
			if (! (error = git_sysdir_expand_global_file(&buf, &cfgval[2])))
				*out = git_buf_detach(&buf);
		} else if (cfgval) {
			*out = git__strdup(cfgval);
		}
	}
	else if (!git_sysdir_find_xdg_file(&buf, fallback)) {
		*out = git_buf_detach(&buf);
	}

	git_config_entry_free(entry);
	git_buf_dispose(&buf);

	return error;
}