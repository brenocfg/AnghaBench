#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  exclude_helpers_from_list (struct string_list*) ; 
 int /*<<< orphan*/  list_aliases (struct string_list*) ; 
 int /*<<< orphan*/  list_all_main_cmds (struct string_list*) ; 
 int /*<<< orphan*/  list_all_other_cmds (struct string_list*) ; 
 int /*<<< orphan*/  list_builtins (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_cmds_by_category (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_cmds_by_config (struct string_list*) ; 
 scalar_t__ match_token (char const*,int,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_git_directory_gently (int*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int list_cmds(const char *spec)
{
	struct string_list list = STRING_LIST_INIT_DUP;
	int i;
	int nongit;

	/*
	* Set up the repository so we can pick up any repo-level config (like
	* completion.commands).
	*/
	setup_git_directory_gently(&nongit);

	while (*spec) {
		const char *sep = strchrnul(spec, ',');
		int len = sep - spec;

		if (match_token(spec, len, "builtins"))
			list_builtins(&list, 0);
		else if (match_token(spec, len, "main"))
			list_all_main_cmds(&list);
		else if (match_token(spec, len, "others"))
			list_all_other_cmds(&list);
		else if (match_token(spec, len, "nohelpers"))
			exclude_helpers_from_list(&list);
		else if (match_token(spec, len, "alias"))
			list_aliases(&list);
		else if (match_token(spec, len, "config"))
			list_cmds_by_config(&list);
		else if (len > 5 && !strncmp(spec, "list-", 5)) {
			struct strbuf sb = STRBUF_INIT;

			strbuf_add(&sb, spec + 5, len - 5);
			list_cmds_by_category(&list, sb.buf);
			strbuf_release(&sb);
		}
		else
			die(_("unsupported command listing type '%s'"), spec);
		spec += len;
		if (*spec == ',')
			spec++;
	}
	for (i = 0; i < list.nr; i++)
		puts(list.items[i].string);
	string_list_clear(&list, 0);
	return 0;
}