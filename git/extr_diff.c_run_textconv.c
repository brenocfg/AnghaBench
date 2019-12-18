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
struct strbuf {int dummy; } ;
struct repository {int dummy; } ;
struct diff_tempfile {int /*<<< orphan*/  name; } ;
struct diff_filespec {int /*<<< orphan*/  path; } ;
struct child_process {int use_shell; char const** argv; int out; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  close (int) ; 
 int error (char*,char const*) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 struct diff_tempfile* prepare_temp_file (struct repository*,int /*<<< orphan*/ ,struct diff_filespec*) ; 
 int /*<<< orphan*/  remove_tempfile () ; 
 scalar_t__ start_command (struct child_process*) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static char *run_textconv(struct repository *r,
			  const char *pgm,
			  struct diff_filespec *spec,
			  size_t *outsize)
{
	struct diff_tempfile *temp;
	const char *argv[3];
	const char **arg = argv;
	struct child_process child = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	int err = 0;

	temp = prepare_temp_file(r, spec->path, spec);
	*arg++ = pgm;
	*arg++ = temp->name;
	*arg = NULL;

	child.use_shell = 1;
	child.argv = argv;
	child.out = -1;
	if (start_command(&child)) {
		remove_tempfile();
		return NULL;
	}

	if (strbuf_read(&buf, child.out, 0) < 0)
		err = error("error reading from textconv command '%s'", pgm);
	close(child.out);

	if (finish_command(&child) || err) {
		strbuf_release(&buf);
		remove_tempfile();
		return NULL;
	}
	remove_tempfile();

	return strbuf_detach(&buf, outsize);
}