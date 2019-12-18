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
struct option {char* member_2; char* member_4; int member_6; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_5; struct batch_options* member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct batch_options {int buffer_output; int follow_symlinks; int all_objects; int unordered; int cmdmode; scalar_t__ enabled; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option const OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option const OPT_CMDMODE (char,char*,int*,int /*<<< orphan*/ ,char) ; 
 struct option const OPT_END () ; 
 struct option const OPT_GROUP (int /*<<< orphan*/ ) ; 
 struct option const OPT_STRING (int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PARSE_OPT_NONEG ; 
 int PARSE_OPT_OPTARG ; 
 int batch_objects (struct batch_options*) ; 
 int /*<<< orphan*/  batch_option_callback ; 
 int /*<<< orphan*/  cat_file_usage ; 
 int cat_one_file (int,char const*,char const*,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ force_path ; 
 int /*<<< orphan*/  git_cat_file_config ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_options (int,char const**,char const*,struct option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option const*) ; 

int cmd_cat_file(int argc, const char **argv, const char *prefix)
{
	int opt = 0;
	const char *exp_type = NULL, *obj_name = NULL;
	struct batch_options batch = {0};
	int unknown_type = 0;

	const struct option options[] = {
		OPT_GROUP(N_("<type> can be one of: blob, tree, commit, tag")),
		OPT_CMDMODE('t', NULL, &opt, N_("show object type"), 't'),
		OPT_CMDMODE('s', NULL, &opt, N_("show object size"), 's'),
		OPT_CMDMODE('e', NULL, &opt,
			    N_("exit with zero when there's no error"), 'e'),
		OPT_CMDMODE('p', NULL, &opt, N_("pretty-print object's content"), 'p'),
		OPT_CMDMODE(0, "textconv", &opt,
			    N_("for blob objects, run textconv on object's content"), 'c'),
		OPT_CMDMODE(0, "filters", &opt,
			    N_("for blob objects, run filters on object's content"), 'w'),
		OPT_STRING(0, "path", &force_path, N_("blob"),
			   N_("use a specific path for --textconv/--filters")),
		OPT_BOOL(0, "allow-unknown-type", &unknown_type,
			  N_("allow -s and -t to work with broken/corrupt objects")),
		OPT_BOOL(0, "buffer", &batch.buffer_output, N_("buffer --batch output")),
		{ OPTION_CALLBACK, 0, "batch", &batch, "format",
			N_("show info and content of objects fed from the standard input"),
			PARSE_OPT_OPTARG | PARSE_OPT_NONEG,
			batch_option_callback },
		{ OPTION_CALLBACK, 0, "batch-check", &batch, "format",
			N_("show info about objects fed from the standard input"),
			PARSE_OPT_OPTARG | PARSE_OPT_NONEG,
			batch_option_callback },
		OPT_BOOL(0, "follow-symlinks", &batch.follow_symlinks,
			 N_("follow in-tree symlinks (used with --batch or --batch-check)")),
		OPT_BOOL(0, "batch-all-objects", &batch.all_objects,
			 N_("show all objects with --batch or --batch-check")),
		OPT_BOOL(0, "unordered", &batch.unordered,
			 N_("do not order --batch-all-objects output")),
		OPT_END()
	};

	git_config(git_cat_file_config, NULL);

	batch.buffer_output = -1;
	argc = parse_options(argc, argv, prefix, options, cat_file_usage, 0);

	if (opt) {
		if (batch.enabled && (opt == 'c' || opt == 'w'))
			batch.cmdmode = opt;
		else if (argc == 1)
			obj_name = argv[0];
		else
			usage_with_options(cat_file_usage, options);
	}
	if (!opt && !batch.enabled) {
		if (argc == 2) {
			exp_type = argv[0];
			obj_name = argv[1];
		} else
			usage_with_options(cat_file_usage, options);
	}
	if (batch.enabled) {
		if (batch.cmdmode != opt || argc)
			usage_with_options(cat_file_usage, options);
		if (batch.cmdmode && batch.all_objects)
			die("--batch-all-objects cannot be combined with "
			    "--textconv nor with --filters");
	}

	if ((batch.follow_symlinks || batch.all_objects) && !batch.enabled) {
		usage_with_options(cat_file_usage, options);
	}

	if (force_path && opt != 'c' && opt != 'w') {
		error("--path=<path> needs --textconv or --filters");
		usage_with_options(cat_file_usage, options);
	}

	if (force_path && batch.enabled) {
		error("--path=<path> incompatible with --batch");
		usage_with_options(cat_file_usage, options);
	}

	if (batch.buffer_output < 0)
		batch.buffer_output = batch.all_objects;

	if (batch.enabled)
		return batch_objects(&batch);

	if (unknown_type && opt != 't' && opt != 's')
		die("git cat-file --allow-unknown-type: use with -s or -t");
	return cat_one_file(opt, exp_type, obj_name, unknown_type);
}