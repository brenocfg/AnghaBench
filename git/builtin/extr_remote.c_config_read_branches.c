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
struct string_list_item {struct branch_info* util; } ;
struct branch_info {char* remote_name; int rebase; int /*<<< orphan*/  merge; } ;

/* Variables and functions */
 int INTERACTIVE_REBASE ; 
 int NORMAL_REBASE ; 
 int REBASE_MERGES ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* abbrev_branch (char const*) ; 
 int /*<<< orphan*/  branch_list ; 
 int git_parse_maybe_bool (char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char*) ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strip_suffix (char const*,char*,size_t*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 
 struct branch_info* xcalloc (int,int) ; 
 char* xmemdupz (char const*,size_t) ; 
 char* xstrdup (char const*) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static int config_read_branches(const char *key, const char *value, void *cb)
{
	if (starts_with(key, "branch.")) {
		const char *orig_key = key;
		char *name;
		struct string_list_item *item;
		struct branch_info *info;
		enum { REMOTE, MERGE, REBASE } type;
		size_t key_len;

		key += 7;
		if (strip_suffix(key, ".remote", &key_len)) {
			name = xmemdupz(key, key_len);
			type = REMOTE;
		} else if (strip_suffix(key, ".merge", &key_len)) {
			name = xmemdupz(key, key_len);
			type = MERGE;
		} else if (strip_suffix(key, ".rebase", &key_len)) {
			name = xmemdupz(key, key_len);
			type = REBASE;
		} else
			return 0;

		item = string_list_insert(&branch_list, name);

		if (!item->util)
			item->util = xcalloc(1, sizeof(struct branch_info));
		info = item->util;
		if (type == REMOTE) {
			if (info->remote_name)
				warning(_("more than one %s"), orig_key);
			info->remote_name = xstrdup(value);
		} else if (type == MERGE) {
			char *space = strchr(value, ' ');
			value = abbrev_branch(value);
			while (space) {
				char *merge;
				merge = xstrndup(value, space - value);
				string_list_append(&info->merge, merge);
				value = abbrev_branch(space + 1);
				space = strchr(value, ' ');
			}
			string_list_append(&info->merge, xstrdup(value));
		} else {
			int v = git_parse_maybe_bool(value);
			if (v >= 0)
				info->rebase = v;
			else if (!strcmp(value, "preserve"))
				info->rebase = NORMAL_REBASE;
			else if (!strcmp(value, "merges"))
				info->rebase = REBASE_MERGES;
			else if (!strcmp(value, "interactive"))
				info->rebase = INTERACTIVE_REBASE;
		}
	}
	return 0;
}