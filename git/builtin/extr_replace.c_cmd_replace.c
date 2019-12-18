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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_BOOL_F (float,char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_CMDMODE (char,char*,int*,int /*<<< orphan*/ ,int) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_NOCOMPLETE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  convert_graft_file (int) ; 
 int create_graft (int,char const**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_replace_ref ; 
 int edit_and_replace (char const*,int,int) ; 
 int for_each_replace_name (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  git_replace_usage ; 
 int list_replace_refs (char const*,char const*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_replace_refs ; 
 int replace_object (char const*,char const*,int) ; 
 int /*<<< orphan*/  usage_msg_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct option*) ; 

int cmd_replace(int argc, const char **argv, const char *prefix)
{
	int force = 0;
	int raw = 0;
	const char *format = NULL;
	enum {
		MODE_UNSPECIFIED = 0,
		MODE_LIST,
		MODE_DELETE,
		MODE_EDIT,
		MODE_GRAFT,
		MODE_CONVERT_GRAFT_FILE,
		MODE_REPLACE
	} cmdmode = MODE_UNSPECIFIED;
	struct option options[] = {
		OPT_CMDMODE('l', "list", &cmdmode, N_("list replace refs"), MODE_LIST),
		OPT_CMDMODE('d', "delete", &cmdmode, N_("delete replace refs"), MODE_DELETE),
		OPT_CMDMODE('e', "edit", &cmdmode, N_("edit existing object"), MODE_EDIT),
		OPT_CMDMODE('g', "graft", &cmdmode, N_("change a commit's parents"), MODE_GRAFT),
		OPT_CMDMODE(0, "convert-graft-file", &cmdmode, N_("convert existing graft file"), MODE_CONVERT_GRAFT_FILE),
		OPT_BOOL_F('f', "force", &force, N_("replace the ref if it exists"),
			   PARSE_OPT_NOCOMPLETE),
		OPT_BOOL(0, "raw", &raw, N_("do not pretty-print contents for --edit")),
		OPT_STRING(0, "format", &format, N_("format"), N_("use this format")),
		OPT_END()
	};

	read_replace_refs = 0;
	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, options, git_replace_usage, 0);

	if (!cmdmode)
		cmdmode = argc ? MODE_REPLACE : MODE_LIST;

	if (format && cmdmode != MODE_LIST)
		usage_msg_opt(_("--format cannot be used when not listing"),
			      git_replace_usage, options);

	if (force &&
	    cmdmode != MODE_REPLACE &&
	    cmdmode != MODE_EDIT &&
	    cmdmode != MODE_GRAFT &&
	    cmdmode != MODE_CONVERT_GRAFT_FILE)
		usage_msg_opt(_("-f only makes sense when writing a replacement"),
			      git_replace_usage, options);

	if (raw && cmdmode != MODE_EDIT)
		usage_msg_opt(_("--raw only makes sense with --edit"),
			      git_replace_usage, options);

	switch (cmdmode) {
	case MODE_DELETE:
		if (argc < 1)
			usage_msg_opt(_("-d needs at least one argument"),
				      git_replace_usage, options);
		return for_each_replace_name(argv, delete_replace_ref);

	case MODE_REPLACE:
		if (argc != 2)
			usage_msg_opt(_("bad number of arguments"),
				      git_replace_usage, options);
		return replace_object(argv[0], argv[1], force);

	case MODE_EDIT:
		if (argc != 1)
			usage_msg_opt(_("-e needs exactly one argument"),
				      git_replace_usage, options);
		return edit_and_replace(argv[0], force, raw);

	case MODE_GRAFT:
		if (argc < 1)
			usage_msg_opt(_("-g needs at least one argument"),
				      git_replace_usage, options);
		return create_graft(argc, argv, force, 0);

	case MODE_CONVERT_GRAFT_FILE:
		if (argc != 0)
			usage_msg_opt(_("--convert-graft-file takes no argument"),
				      git_replace_usage, options);
		return !!convert_graft_file(force);

	case MODE_LIST:
		if (argc > 1)
			usage_msg_opt(_("only one pattern can be given with -l"),
				      git_replace_usage, options);
		return list_replace_refs(argv[0], format);

	default:
		BUG("invalid cmdmode %d", (int)cmdmode);
	}
}