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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct create_tag_options {scalar_t__ cleanup_mode; int /*<<< orphan*/  sign; scalar_t__ message_given; scalar_t__ use_editor; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 scalar_t__ CLEANUP_ALL ; 
 scalar_t__ CLEANUP_NONE ; 
 int /*<<< orphan*/  IDENT_STRICT ; 
 int OBJ_NONE ; 
 int OBJ_TAG ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 scalar_t__ advice_nested_tag ; 
 int /*<<< orphan*/  advise (char*,char const*,char const*) ; 
 scalar_t__ build_tag_object (struct strbuf*,int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  comment_line_char ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_errno (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_committer_info (int /*<<< orphan*/ ) ; 
 char* git_pathdup (char*) ; 
 int /*<<< orphan*/  is_null_oid (struct object_id*) ; 
 scalar_t__ launch_editor (char*,struct strbuf*,int /*<<< orphan*/ *) ; 
 char* message_advice_nested_tag ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_stripspace (struct strbuf*,int) ; 
 char* tag_template ; 
 char* tag_template_nocleanup ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int) ; 
 int /*<<< orphan*/  unlink_or_warn (char*) ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tag_body (int,struct object_id*) ; 

__attribute__((used)) static void create_tag(const struct object_id *object, const char *object_ref,
		       const char *tag,
		       struct strbuf *buf, struct create_tag_options *opt,
		       struct object_id *prev, struct object_id *result)
{
	enum object_type type;
	struct strbuf header = STRBUF_INIT;
	char *path = NULL;

	type = oid_object_info(the_repository, object, NULL);
	if (type <= OBJ_NONE)
		die(_("bad object type."));

	if (type == OBJ_TAG && advice_nested_tag)
		advise(_(message_advice_nested_tag), tag, object_ref);

	strbuf_addf(&header,
		    "object %s\n"
		    "type %s\n"
		    "tag %s\n"
		    "tagger %s\n\n",
		    oid_to_hex(object),
		    type_name(type),
		    tag,
		    git_committer_info(IDENT_STRICT));

	if (!opt->message_given || opt->use_editor) {
		int fd;

		/* write the template message before editing: */
		path = git_pathdup("TAG_EDITMSG");
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (fd < 0)
			die_errno(_("could not create file '%s'"), path);

		if (opt->message_given) {
			write_or_die(fd, buf->buf, buf->len);
			strbuf_reset(buf);
		} else if (!is_null_oid(prev)) {
			write_tag_body(fd, prev);
		} else {
			struct strbuf buf = STRBUF_INIT;
			strbuf_addch(&buf, '\n');
			if (opt->cleanup_mode == CLEANUP_ALL)
				strbuf_commented_addf(&buf, _(tag_template), tag, comment_line_char);
			else
				strbuf_commented_addf(&buf, _(tag_template_nocleanup), tag, comment_line_char);
			write_or_die(fd, buf.buf, buf.len);
			strbuf_release(&buf);
		}
		close(fd);

		if (launch_editor(path, buf, NULL)) {
			fprintf(stderr,
			_("Please supply the message using either -m or -F option.\n"));
			exit(1);
		}
	}

	if (opt->cleanup_mode != CLEANUP_NONE)
		strbuf_stripspace(buf, opt->cleanup_mode == CLEANUP_ALL);

	if (!opt->message_given && !buf->len)
		die(_("no tag message?"));

	strbuf_insert(buf, 0, header.buf, header.len);
	strbuf_release(&header);

	if (build_tag_object(buf, opt->sign, result) < 0) {
		if (path)
			fprintf(stderr, _("The tag message has been left in %s\n"),
				path);
		exit(128);
	}
	if (path) {
		unlink_or_warn(path);
		free(path);
	}
}