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
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct option {int dummy; } ;
struct column_options {int width; char const* indent; int nl; int padding; } ;
typedef  int /*<<< orphan*/  copts ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_COLUMN (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_INTEGER (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  builtin_column_usage ; 
 int colopts ; 
 int /*<<< orphan*/  column_config ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_colopts (int*,int) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (struct column_options*,int /*<<< orphan*/ ,int) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_columns (struct string_list*,int,struct column_options*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

int cmd_column(int argc, const char **argv, const char *prefix)
{
	struct string_list list = STRING_LIST_INIT_DUP;
	struct strbuf sb = STRBUF_INIT;
	struct column_options copts;
	const char *command = NULL, *real_command = NULL;
	struct option options[] = {
		OPT_STRING(0, "command", &real_command, N_("name"), N_("lookup config vars")),
		OPT_COLUMN(0, "mode", &colopts, N_("layout to use")),
		OPT_INTEGER(0, "raw-mode", &colopts, N_("layout to use")),
		OPT_INTEGER(0, "width", &copts.width, N_("Maximum width")),
		OPT_STRING(0, "indent", &copts.indent, N_("string"), N_("Padding space on left border")),
		OPT_INTEGER(0, "nl", &copts.nl, N_("Padding space on right border")),
		OPT_INTEGER(0, "padding", &copts.padding, N_("Padding space between columns")),
		OPT_END()
	};

	/* This one is special and must be the first one */
	if (argc > 1 && starts_with(argv[1], "--command=")) {
		command = argv[1] + 10;
		git_config(column_config, (void *)command);
	} else
		git_config(column_config, NULL);

	memset(&copts, 0, sizeof(copts));
	copts.padding = 1;
	argc = parse_options(argc, argv, prefix, options, builtin_column_usage, 0);
	if (argc)
		usage_with_options(builtin_column_usage, options);
	if (real_command || command) {
		if (!real_command || !command || strcmp(real_command, command))
			die(_("--command must be the first argument"));
	}
	finalize_colopts(&colopts, -1);
	while (!strbuf_getline(&sb, stdin))
		string_list_append(&list, sb.buf);

	print_columns(&list, colopts, &copts);
	return 0;
}