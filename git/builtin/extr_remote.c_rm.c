#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {int /*<<< orphan*/  string; struct branch_info* util; } ;
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {char const* buf; } ;
struct remote {int /*<<< orphan*/  name; } ;
struct option {int dummy; } ;
struct known_remotes {struct remote* to_delete; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct branches_for_remote {struct remote* remote; struct known_remotes* keep; struct string_list* skipped; struct string_list* branches; } ;
struct branch_info {scalar_t__ remote_name; } ;
typedef  int /*<<< orphan*/  cb_data ;
struct TYPE_4__ {int nr; struct string_list_item* items; } ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 int CONFIG_NOTHING_SET ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_branch_for_removal ; 
 int /*<<< orphan*/  add_known_remote ; 
 TYPE_2__ branch_list ; 
 int /*<<< orphan*/  builtin_remote_rm_usage ; 
 int delete_refs (char*,struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int for_each_ref (int /*<<< orphan*/ ,struct branches_for_remote*) ; 
 int /*<<< orphan*/  for_each_remote (int /*<<< orphan*/ ,struct known_remotes*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_config_rename_section (char const*,int /*<<< orphan*/ *) ; 
 int git_config_set_gently (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct branches_for_remote*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_branches () ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  remote_is_configured (struct remote*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int rm(int argc, const char **argv)
{
	struct option options[] = {
		OPT_END()
	};
	struct remote *remote;
	struct strbuf buf = STRBUF_INIT;
	struct known_remotes known_remotes = { NULL, NULL };
	struct string_list branches = STRING_LIST_INIT_DUP;
	struct string_list skipped = STRING_LIST_INIT_DUP;
	struct branches_for_remote cb_data;
	int i, result;

	memset(&cb_data, 0, sizeof(cb_data));
	cb_data.branches = &branches;
	cb_data.skipped = &skipped;
	cb_data.keep = &known_remotes;

	if (argc != 2)
		usage_with_options(builtin_remote_rm_usage, options);

	remote = remote_get(argv[1]);
	if (!remote_is_configured(remote, 1))
		die(_("No such remote: '%s'"), argv[1]);

	known_remotes.to_delete = remote;
	for_each_remote(add_known_remote, &known_remotes);

	read_branches();
	for (i = 0; i < branch_list.nr; i++) {
		struct string_list_item *item = branch_list.items + i;
		struct branch_info *info = item->util;
		if (info->remote_name && !strcmp(info->remote_name, remote->name)) {
			const char *keys[] = { "remote", "merge", NULL }, **k;
			for (k = keys; *k; k++) {
				strbuf_reset(&buf);
				strbuf_addf(&buf, "branch.%s.%s",
						item->string, *k);
				result = git_config_set_gently(buf.buf, NULL);
				if (result && result != CONFIG_NOTHING_SET)
					die(_("could not unset '%s'"), buf.buf);
			}
		}
	}

	/*
	 * We cannot just pass a function to for_each_ref() which deletes
	 * the branches one by one, since for_each_ref() relies on cached
	 * refs, which are invalidated when deleting a branch.
	 */
	cb_data.remote = remote;
	result = for_each_ref(add_branch_for_removal, &cb_data);
	strbuf_release(&buf);

	if (!result)
		result = delete_refs("remote: remove", &branches, REF_NO_DEREF);
	string_list_clear(&branches, 0);

	if (skipped.nr) {
		fprintf_ln(stderr,
			   Q_("Note: A branch outside the refs/remotes/ hierarchy was not removed;\n"
			      "to delete it, use:",
			      "Note: Some branches outside the refs/remotes/ hierarchy were not removed;\n"
			      "to delete them, use:",
			      skipped.nr));
		for (i = 0; i < skipped.nr; i++)
			fprintf(stderr, "  git branch -d %s\n",
				skipped.items[i].string);
	}
	string_list_clear(&skipped, 0);

	if (!result) {
		strbuf_addf(&buf, "remote.%s", remote->name);
		if (git_config_rename_section(buf.buf, NULL) < 1)
			return error(_("Could not remove config section '%s'"), buf.buf);
	}

	return result;
}