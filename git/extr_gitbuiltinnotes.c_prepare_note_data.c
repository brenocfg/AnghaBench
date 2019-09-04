#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct note_data {TYPE_1__ buf; int /*<<< orphan*/  edit_path; scalar_t__ given; scalar_t__ use_editor; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  copy_obj_to_fd (int,struct object_id const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pathdup (char*) ; 
 scalar_t__ launch_editor (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* note_template ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_stripspace (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  write_commented_object (int,struct object_id const*) ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_note_data(const struct object_id *object, struct note_data *d,
		const struct object_id *old_note)
{
	if (d->use_editor || !d->given) {
		int fd;
		struct strbuf buf = STRBUF_INIT;

		/* write the template message before editing: */
		d->edit_path = git_pathdup("NOTES_EDITMSG");
		fd = open(d->edit_path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (fd < 0)
			die_errno(_("could not create file '%s'"), d->edit_path);

		if (d->given)
			write_or_die(fd, d->buf.buf, d->buf.len);
		else if (old_note)
			copy_obj_to_fd(fd, old_note);

		strbuf_addch(&buf, '\n');
		strbuf_add_commented_lines(&buf, "\n", strlen("\n"));
		strbuf_add_commented_lines(&buf, _(note_template), strlen(_(note_template)));
		strbuf_addch(&buf, '\n');
		write_or_die(fd, buf.buf, buf.len);

		write_commented_object(fd, object);

		close(fd);
		strbuf_release(&buf);
		strbuf_reset(&d->buf);

		if (launch_editor(d->edit_path, &d->buf, NULL)) {
			die(_("please supply the note contents using either -m or -F option"));
		}
		strbuf_stripspace(&d->buf, 1);
	}
}