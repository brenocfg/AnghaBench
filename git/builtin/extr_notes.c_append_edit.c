#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct option {char member_1; char* member_2; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; struct note_data* member_3; int /*<<< orphan*/  member_0; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct notes_tree {int dummy; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct note_data {TYPE_1__ buf; scalar_t__ given; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  NOTES_INIT_WRITABLE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_ARGV0 ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  STRBUF_INIT ; 
 char* _ (char*) ; 
 scalar_t__ add_note (struct notes_tree*,struct object_id*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  combine_notes_overwrite ; 
 int /*<<< orphan*/  commit_notes (int /*<<< orphan*/ ,struct notes_tree*,char*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_note_data (struct note_data*) ; 
 int /*<<< orphan*/  free_notes (struct notes_tree*) ; 
 struct object_id* get_note (struct notes_tree*,struct object_id*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 char** git_notes_append_usage ; 
 char** git_notes_edit_usage ; 
 struct notes_tree* init_notes_check (char const*,int /*<<< orphan*/ ) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  parse_file_arg ; 
 int /*<<< orphan*/  parse_msg_arg ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_reedit_arg ; 
 int /*<<< orphan*/  parse_reuse_arg ; 
 int /*<<< orphan*/  prepare_note_data (struct object_id*,struct note_data*,struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  remove_note (struct notes_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_grow (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  strbuf_insert (TYPE_1__*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option*) ; 
 int /*<<< orphan*/  write_note_data (struct note_data*,struct object_id*) ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static int append_edit(int argc, const char **argv, const char *prefix)
{
	int allow_empty = 0;
	const char *object_ref;
	struct notes_tree *t;
	struct object_id object, new_note;
	const struct object_id *note;
	char *logmsg;
	const char * const *usage;
	struct note_data d = { 0, 0, NULL, STRBUF_INIT };
	struct option options[] = {
		{ OPTION_CALLBACK, 'm', "message", &d, N_("message"),
			N_("note contents as a string"), PARSE_OPT_NONEG,
			parse_msg_arg},
		{ OPTION_CALLBACK, 'F', "file", &d, N_("file"),
			N_("note contents in a file"), PARSE_OPT_NONEG,
			parse_file_arg},
		{ OPTION_CALLBACK, 'c', "reedit-message", &d, N_("object"),
			N_("reuse and edit specified note object"), PARSE_OPT_NONEG,
			parse_reedit_arg},
		{ OPTION_CALLBACK, 'C', "reuse-message", &d, N_("object"),
			N_("reuse specified note object"), PARSE_OPT_NONEG,
			parse_reuse_arg},
		OPT_BOOL(0, "allow-empty", &allow_empty,
			N_("allow storing empty note")),
		OPT_END()
	};
	int edit = !strcmp(argv[0], "edit");

	usage = edit ? git_notes_edit_usage : git_notes_append_usage;
	argc = parse_options(argc, argv, prefix, options, usage,
			     PARSE_OPT_KEEP_ARGV0);

	if (2 < argc) {
		error(_("too many parameters"));
		usage_with_options(usage, options);
	}

	if (d.given && edit)
		fprintf(stderr, _("The -m/-F/-c/-C options have been deprecated "
			"for the 'edit' subcommand.\n"
			"Please use 'git notes add -f -m/-F/-c/-C' instead.\n"));

	object_ref = 1 < argc ? argv[1] : "HEAD";

	if (get_oid(object_ref, &object))
		die(_("failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check(argv[0], NOTES_INIT_WRITABLE);
	note = get_note(t, &object);

	prepare_note_data(&object, &d, edit && note ? note : NULL);

	if (note && !edit) {
		/* Append buf to previous note contents */
		unsigned long size;
		enum object_type type;
		char *prev_buf = read_object_file(note, &type, &size);

		strbuf_grow(&d.buf, size + 1);
		if (d.buf.len && prev_buf && size)
			strbuf_insert(&d.buf, 0, "\n", 1);
		if (prev_buf && size)
			strbuf_insert(&d.buf, 0, prev_buf, size);
		free(prev_buf);
	}

	if (d.buf.len || allow_empty) {
		write_note_data(&d, &new_note);
		if (add_note(t, &object, &new_note, combine_notes_overwrite))
			BUG("combine_notes_overwrite failed");
		logmsg = xstrfmt("Notes added by 'git notes %s'", argv[0]);
	} else {
		fprintf(stderr, _("Removing note for object %s\n"),
			oid_to_hex(&object));
		remove_note(t, object.hash);
		logmsg = xstrfmt("Notes removed by 'git notes %s'", argv[0]);
	}
	commit_notes(the_repository, t, logmsg);

	free(logmsg);
	free_note_data(&d);
	free_notes(t);
	return 0;
}