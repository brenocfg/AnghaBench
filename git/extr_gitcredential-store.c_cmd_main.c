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
struct string_list {int /*<<< orphan*/  nr; } ;
struct option {int dummy; } ;
struct credential {int dummy; } ;

/* Variables and functions */
 struct credential CREDENTIAL_INIT ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char**,char*,char*) ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 scalar_t__ credential_read (struct credential*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 char* expand_user_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_credential (struct string_list*,struct credential*) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_credential (struct string_list*,struct credential*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  store_credential (struct string_list*,struct credential*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_append_nodup (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option*) ; 
 char* xdg_config_home (char*) ; 

int cmd_main(int argc, const char **argv)
{
	const char * const usage[] = {
		"git credential-store [<options>] <action>",
		NULL
	};
	const char *op;
	struct credential c = CREDENTIAL_INIT;
	struct string_list fns = STRING_LIST_INIT_DUP;
	char *file = NULL;
	struct option options[] = {
		OPT_STRING(0, "file", &file, "path",
			   "fetch and store credentials in <path>"),
		OPT_END()
	};

	umask(077);

	argc = parse_options(argc, (const char **)argv, NULL, options, usage, 0);
	if (argc != 1)
		usage_with_options(usage, options);
	op = argv[0];

	if (file) {
		string_list_append(&fns, file);
	} else {
		if ((file = expand_user_path("~/.git-credentials", 0)))
			string_list_append_nodup(&fns, file);
		file = xdg_config_home("credentials");
		if (file)
			string_list_append_nodup(&fns, file);
	}
	if (!fns.nr)
		die("unable to set up default path; use --file");

	if (credential_read(&c, stdin) < 0)
		die("unable to read credential");

	if (!strcmp(op, "get"))
		lookup_credential(&fns, &c);
	else if (!strcmp(op, "erase"))
		remove_credential(&fns, &c);
	else if (!strcmp(op, "store"))
		store_credential(&fns, &c);
	else
		; /* Ignore unknown operation. */

	string_list_clear(&fns, 0);
	return 0;
}