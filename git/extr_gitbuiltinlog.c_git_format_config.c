#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  COVER_AUTO ; 
 int /*<<< orphan*/  COVER_OFF ; 
 int /*<<< orphan*/  COVER_ON ; 
 int /*<<< orphan*/  IDENT_NO_DATE ; 
 int THREAD_DEEP ; 
 int THREAD_SHALLOW ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_header (char const*) ; 
 int auto_number ; 
 void* base_auto ; 
 int /*<<< orphan*/  config_cover_letter ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  config_output_directory ; 
 void* default_attach ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 void* do_signoff ; 
 int /*<<< orphan*/  extra_cc ; 
 int /*<<< orphan*/  extra_to ; 
 int /*<<< orphan*/  fmt_patch_suffix ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * from ; 
 char const* git_committer_info (int /*<<< orphan*/ ) ; 
 void* git_config_bool (char const*,char const*) ; 
 int git_config_pathname (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_log_config (char const*,char const*,void*) ; 
 int git_parse_maybe_bool (char const*) ; 
 char const* git_version_string ; 
 void* numbered ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  signature_file ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char const*) ; 
 int thread ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static int git_format_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "format.headers")) {
		if (!value)
			die(_("format.headers without value"));
		add_header(value);
		return 0;
	}
	if (!strcmp(var, "format.suffix"))
		return git_config_string(&fmt_patch_suffix, var, value);
	if (!strcmp(var, "format.to")) {
		if (!value)
			return config_error_nonbool(var);
		string_list_append(&extra_to, value);
		return 0;
	}
	if (!strcmp(var, "format.cc")) {
		if (!value)
			return config_error_nonbool(var);
		string_list_append(&extra_cc, value);
		return 0;
	}
	if (!strcmp(var, "diff.color") || !strcmp(var, "color.diff") ||
	    !strcmp(var, "color.ui") || !strcmp(var, "diff.submodule")) {
		return 0;
	}
	if (!strcmp(var, "format.numbered")) {
		if (value && !strcasecmp(value, "auto")) {
			auto_number = 1;
			return 0;
		}
		numbered = git_config_bool(var, value);
		auto_number = auto_number && numbered;
		return 0;
	}
	if (!strcmp(var, "format.attach")) {
		if (value && *value)
			default_attach = xstrdup(value);
		else
			default_attach = xstrdup(git_version_string);
		return 0;
	}
	if (!strcmp(var, "format.thread")) {
		if (value && !strcasecmp(value, "deep")) {
			thread = THREAD_DEEP;
			return 0;
		}
		if (value && !strcasecmp(value, "shallow")) {
			thread = THREAD_SHALLOW;
			return 0;
		}
		thread = git_config_bool(var, value) && THREAD_SHALLOW;
		return 0;
	}
	if (!strcmp(var, "format.signoff")) {
		do_signoff = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "format.signature"))
		return git_config_string(&signature, var, value);
	if (!strcmp(var, "format.signaturefile"))
		return git_config_pathname(&signature_file, var, value);
	if (!strcmp(var, "format.coverletter")) {
		if (value && !strcasecmp(value, "auto")) {
			config_cover_letter = COVER_AUTO;
			return 0;
		}
		config_cover_letter = git_config_bool(var, value) ? COVER_ON : COVER_OFF;
		return 0;
	}
	if (!strcmp(var, "format.outputdirectory"))
		return git_config_string(&config_output_directory, var, value);
	if (!strcmp(var, "format.useautobase")) {
		base_auto = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "format.from")) {
		int b = git_parse_maybe_bool(value);
		free(from);
		if (b < 0)
			from = xstrdup(value);
		else if (b)
			from = xstrdup(git_committer_info(IDENT_NO_DATE));
		else
			from = NULL;
		return 0;
	}

	return git_log_config(var, value, cb);
}