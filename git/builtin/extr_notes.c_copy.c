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
struct object_id {int dummy; } ;
struct notes_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  NOTES_INIT_WRITABLE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__FORCE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_NOCOMPLETE ; 
 char* _ (char*) ; 
 scalar_t__ add_note (struct notes_tree*,struct object_id*,struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  combine_notes_overwrite ; 
 int /*<<< orphan*/  commit_notes (int /*<<< orphan*/ ,struct notes_tree*,char*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free_notes (struct notes_tree*) ; 
 struct object_id* get_note (struct notes_tree*,struct object_id*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_notes_copy_usage ; 
 struct notes_tree* init_notes_check (char*,int /*<<< orphan*/ ) ; 
 int notes_copy_from_stdin (int,char const*) ; 
 char* oid_to_hex (struct object_id*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int copy(int argc, const char **argv, const char *prefix)
{
	int retval = 0, force = 0, from_stdin = 0;
	const struct object_id *from_note, *note;
	const char *object_ref;
	struct object_id object, from_obj;
	struct notes_tree *t;
	const char *rewrite_cmd = NULL;
	struct option options[] = {
		OPT__FORCE(&force, N_("replace existing notes"), PARSE_OPT_NOCOMPLETE),
		OPT_BOOL(0, "stdin", &from_stdin, N_("read objects from stdin")),
		OPT_STRING(0, "for-rewrite", &rewrite_cmd, N_("command"),
			   N_("load rewriting config for <command> (implies "
			      "--stdin)")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, git_notes_copy_usage,
			     0);

	if (from_stdin || rewrite_cmd) {
		if (argc) {
			error(_("too many parameters"));
			usage_with_options(git_notes_copy_usage, options);
		} else {
			return notes_copy_from_stdin(force, rewrite_cmd);
		}
	}

	if (argc < 1) {
		error(_("too few parameters"));
		usage_with_options(git_notes_copy_usage, options);
	}
	if (2 < argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_copy_usage, options);
	}

	if (get_oid(argv[0], &from_obj))
		die(_("failed to resolve '%s' as a valid ref."), argv[0]);

	object_ref = 1 < argc ? argv[1] : "HEAD";

	if (get_oid(object_ref, &object))
		die(_("failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("copy", NOTES_INIT_WRITABLE);
	note = get_note(t, &object);

	if (note) {
		if (!force) {
			retval = error(_("Cannot copy notes. Found existing "
				       "notes for object %s. Use '-f' to "
				       "overwrite existing notes"),
				       oid_to_hex(&object));
			goto out;
		}
		fprintf(stderr, _("Overwriting existing notes for object %s\n"),
			oid_to_hex(&object));
	}

	from_note = get_note(t, &from_obj);
	if (!from_note) {
		retval = error(_("missing notes on source object %s. Cannot "
			       "copy."), oid_to_hex(&from_obj));
		goto out;
	}

	if (add_note(t, &object, from_note, combine_notes_overwrite))
		BUG("combine_notes_overwrite failed");
	commit_notes(the_repository, t,
		     "Notes added by 'git notes copy'");
out:
	free_notes(t);
	return retval;
}