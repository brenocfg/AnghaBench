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
struct option {char* member_2; int* member_3; int member_6; int member_8; int /*<<< orphan*/ * member_7; int /*<<< orphan*/  member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct object_id {int dummy; } ;
struct object_array {int nr; TYPE_1__* objects; } ;
struct object {scalar_t__ type; } ;
struct name_ref_data {int name_only; int tags_only; int /*<<< orphan*/  exclude_filters; int /*<<< orphan*/  ref_filters; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct commit {scalar_t__ date; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/ * name; struct object* item; } ;

/* Variables and functions */
 scalar_t__ CUTOFF_DATE_SLOP ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct object_array OBJECT_ARRAY_INIT ; 
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  OPTION_SET_INT ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_GROUP (char*) ; 
 struct option OPT_STRING_LIST (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_NOARG ; 
 int /*<<< orphan*/  STRING_LIST_INIT_NODUP ; 
 scalar_t__ TIME_MIN ; 
 int /*<<< orphan*/  UNLEAK (struct object_array) ; 
 int /*<<< orphan*/  add_object_array (struct object*,char const*,struct object_array*) ; 
 scalar_t__ cutoff ; 
 struct object* deref_tag (int /*<<< orphan*/ ,struct object*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct name_ref_data*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct object* get_indexed_object (int) ; 
 int get_max_object_index () ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  init_commit_rev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_ref ; 
 int /*<<< orphan*/  name_rev_line (char*,struct name_ref_data*) ; 
 int /*<<< orphan*/  name_rev_usage ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rev_names ; 
 int /*<<< orphan*/  show_name (struct object*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

int cmd_name_rev(int argc, const char **argv, const char *prefix)
{
	struct object_array revs = OBJECT_ARRAY_INIT;
	int all = 0, transform_stdin = 0, allow_undefined = 1, always = 0, peel_tag = 0;
	struct name_ref_data data = { 0, 0, STRING_LIST_INIT_NODUP, STRING_LIST_INIT_NODUP };
	struct option opts[] = {
		OPT_BOOL(0, "name-only", &data.name_only, N_("print only names (no SHA-1)")),
		OPT_BOOL(0, "tags", &data.tags_only, N_("only use tags to name the commits")),
		OPT_STRING_LIST(0, "refs", &data.ref_filters, N_("pattern"),
				   N_("only use refs matching <pattern>")),
		OPT_STRING_LIST(0, "exclude", &data.exclude_filters, N_("pattern"),
				   N_("ignore refs matching <pattern>")),
		OPT_GROUP(""),
		OPT_BOOL(0, "all", &all, N_("list all commits reachable from all refs")),
		OPT_BOOL(0, "stdin", &transform_stdin, N_("read from stdin")),
		OPT_BOOL(0, "undefined", &allow_undefined, N_("allow to print `undefined` names (default)")),
		OPT_BOOL(0, "always",     &always,
			   N_("show abbreviated commit object as fallback")),
		{
			/* A Hidden OPT_BOOL */
			OPTION_SET_INT, 0, "peel-tag", &peel_tag, NULL,
			N_("dereference tags in the input (internal use)"),
			PARSE_OPT_NOARG | PARSE_OPT_HIDDEN, NULL, 1,
		},
		OPT_END(),
	};

	init_commit_rev_name(&rev_names);
	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, opts, name_rev_usage, 0);
	if (all + transform_stdin + !!argc > 1) {
		error("Specify either a list, or --all, not both!");
		usage_with_options(name_rev_usage, opts);
	}
	if (all || transform_stdin)
		cutoff = 0;

	for (; argc; argc--, argv++) {
		struct object_id oid;
		struct object *object;
		struct commit *commit;

		if (get_oid(*argv, &oid)) {
			fprintf(stderr, "Could not get sha1 for %s. Skipping.\n",
					*argv);
			continue;
		}

		commit = NULL;
		object = parse_object(the_repository, &oid);
		if (object) {
			struct object *peeled = deref_tag(the_repository,
							  object, *argv, 0);
			if (peeled && peeled->type == OBJ_COMMIT)
				commit = (struct commit *)peeled;
		}

		if (!object) {
			fprintf(stderr, "Could not get object for %s. Skipping.\n",
					*argv);
			continue;
		}

		if (commit) {
			if (cutoff > commit->date)
				cutoff = commit->date;
		}

		if (peel_tag) {
			if (!commit) {
				fprintf(stderr, "Could not get commit for %s. Skipping.\n",
					*argv);
				continue;
			}
			object = (struct object *)commit;
		}
		add_object_array(object, *argv, &revs);
	}

	if (cutoff) {
		/* check for undeflow */
		if (cutoff > TIME_MIN + CUTOFF_DATE_SLOP)
			cutoff = cutoff - CUTOFF_DATE_SLOP;
		else
			cutoff = TIME_MIN;
	}
	for_each_ref(name_ref, &data);

	if (transform_stdin) {
		char buffer[2048];

		while (!feof(stdin)) {
			char *p = fgets(buffer, sizeof(buffer), stdin);
			if (!p)
				break;
			name_rev_line(p, &data);
		}
	} else if (all) {
		int i, max;

		max = get_max_object_index();
		for (i = 0; i < max; i++) {
			struct object *obj = get_indexed_object(i);
			if (!obj || obj->type != OBJ_COMMIT)
				continue;
			show_name(obj, NULL,
				  always, allow_undefined, data.name_only);
		}
	} else {
		int i;
		for (i = 0; i < revs.nr; i++)
			show_name(revs.objects[i].item, revs.objects[i].name,
				  always, allow_undefined, data.name_only);
	}

	UNLEAK(revs);
	return 0;
}