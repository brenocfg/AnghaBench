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
struct tree {int dummy; } ;
struct tag {char const* tag; } ;
struct setup_revision_opt {char* def; int /*<<< orphan*/  tweak; } ;
struct TYPE_4__ {int nr; int alloc; struct object_array_entry* objects; } ;
struct TYPE_3__ {int stat_width; int /*<<< orphan*/  file; } ;
struct rev_info {int diff; int always_show_header; int shown_one; TYPE_2__ pending; TYPE_1__ diffopt; int /*<<< orphan*/  no_walk; } ;
struct pathspec {char* def; int /*<<< orphan*/  tweak; } ;
struct object_id {int dummy; } ;
struct object_array_entry {char* name; struct object* item; } ;
struct object {int type; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  match_all ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_COMMIT ; 
 int /*<<< orphan*/  DIFF_RESET ; 
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  REVISION_WALK_NO_WALK_SORTED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_object_array (struct object*,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  cmd_log_init (int,char const**,char const*,struct rev_info*,struct setup_revision_opt*) ; 
 int cmd_log_walk (struct rev_info*) ; 
 char* diff_get_color_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (struct object_array_entry*) ; 
 struct object_id* get_tagged_oid (struct tag*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_log_config ; 
 int /*<<< orphan*/  init_log_defaults () ; 
 int /*<<< orphan*/  memset (struct setup_revision_opt*,int /*<<< orphan*/ ,int) ; 
 int oid_to_hex (struct object_id*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  read_tree_recursive (int /*<<< orphan*/ ,struct tree*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct setup_revision_opt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int show_blob_object (int /*<<< orphan*/ *,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  show_setup_revisions_tweak ; 
 int show_tag_object (int /*<<< orphan*/ *,struct rev_info*) ; 
 int /*<<< orphan*/  show_tree_object ; 
 int /*<<< orphan*/  the_repository ; 

int cmd_show(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	struct object_array_entry *objects;
	struct setup_revision_opt opt;
	struct pathspec match_all;
	int i, count, ret = 0;

	init_log_defaults();
	git_config(git_log_config, NULL);

	memset(&match_all, 0, sizeof(match_all));
	repo_init_revisions(the_repository, &rev, prefix);
	rev.diff = 1;
	rev.always_show_header = 1;
	rev.no_walk = REVISION_WALK_NO_WALK_SORTED;
	rev.diffopt.stat_width = -1; 	/* Scale to real terminal size */

	memset(&opt, 0, sizeof(opt));
	opt.def = "HEAD";
	opt.tweak = show_setup_revisions_tweak;
	cmd_log_init(argc, argv, prefix, &rev, &opt);

	if (!rev.no_walk)
		return cmd_log_walk(&rev);

	count = rev.pending.nr;
	objects = rev.pending.objects;
	for (i = 0; i < count && !ret; i++) {
		struct object *o = objects[i].item;
		const char *name = objects[i].name;
		switch (o->type) {
		case OBJ_BLOB:
			ret = show_blob_object(&o->oid, &rev, name);
			break;
		case OBJ_TAG: {
			struct tag *t = (struct tag *)o;
			struct object_id *oid = get_tagged_oid(t);

			if (rev.shown_one)
				putchar('\n');
			fprintf(rev.diffopt.file, "%stag %s%s\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					t->tag,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			ret = show_tag_object(&o->oid, &rev);
			rev.shown_one = 1;
			if (ret)
				break;
			o = parse_object(the_repository, oid);
			if (!o)
				ret = error(_("could not read object %s"),
					    oid_to_hex(oid));
			objects[i].item = o;
			i--;
			break;
		}
		case OBJ_TREE:
			if (rev.shown_one)
				putchar('\n');
			fprintf(rev.diffopt.file, "%stree %s%s\n\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					name,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			read_tree_recursive(the_repository, (struct tree *)o, "",
					    0, 0, &match_all, show_tree_object,
					    rev.diffopt.file);
			rev.shown_one = 1;
			break;
		case OBJ_COMMIT:
			rev.pending.nr = rev.pending.alloc = 0;
			rev.pending.objects = NULL;
			add_object_array(o, name, &rev.pending);
			ret = cmd_log_walk(&rev);
			break;
		default:
			ret = error(_("unknown type: %d"), o->type);
		}
	}
	free(objects);
	return ret;
}