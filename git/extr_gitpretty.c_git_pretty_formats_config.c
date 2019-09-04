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
struct cmt_fmt_map {int is_tformat; int is_alias; char const* user_format; int /*<<< orphan*/  format; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cmt_fmt_map*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMIT_FMT_USERFORMAT ; 
 int builtin_formats_len ; 
 struct cmt_fmt_map* commit_formats ; 
 int /*<<< orphan*/  commit_formats_alloc ; 
 int commit_formats_len ; 
 scalar_t__ git_config_string (char const**,char const*,char const*) ; 
 int /*<<< orphan*/  memset (struct cmt_fmt_map*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int git_pretty_formats_config(const char *var, const char *value, void *cb)
{
	struct cmt_fmt_map *commit_format = NULL;
	const char *name;
	const char *fmt;
	int i;

	if (!skip_prefix(var, "pretty.", &name))
		return 0;

	for (i = 0; i < builtin_formats_len; i++) {
		if (!strcmp(commit_formats[i].name, name))
			return 0;
	}

	for (i = builtin_formats_len; i < commit_formats_len; i++) {
		if (!strcmp(commit_formats[i].name, name)) {
			commit_format = &commit_formats[i];
			break;
		}
	}

	if (!commit_format) {
		ALLOC_GROW(commit_formats, commit_formats_len+1,
			   commit_formats_alloc);
		commit_format = &commit_formats[commit_formats_len];
		memset(commit_format, 0, sizeof(*commit_format));
		commit_formats_len++;
	}

	commit_format->name = xstrdup(name);
	commit_format->format = CMIT_FMT_USERFORMAT;
	if (git_config_string(&fmt, var, value))
		return -1;

	if (skip_prefix(fmt, "format:", &fmt))
		commit_format->is_tformat = 0;
	else if (skip_prefix(fmt, "tformat:", &fmt) || strchr(fmt, '%'))
		commit_format->is_tformat = 1;
	else
		commit_format->is_alias = 1;
	commit_format->user_format = fmt;

	return 0;
}