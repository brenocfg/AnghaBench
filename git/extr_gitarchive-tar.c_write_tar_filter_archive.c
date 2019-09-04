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
struct strbuf {char* buf; } ;
struct child_process {char const** argv; int use_shell; int in; } ;
struct archiver_args {int /*<<< orphan*/  compression_level; } ;
struct archiver {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,...) ; 
 scalar_t__ dup2 (int,int) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int write_tar_archive (struct archiver const*,struct archiver_args*) ; 

__attribute__((used)) static int write_tar_filter_archive(const struct archiver *ar,
				    struct archiver_args *args)
{
	struct strbuf cmd = STRBUF_INIT;
	struct child_process filter = CHILD_PROCESS_INIT;
	const char *argv[2];
	int r;

	if (!ar->data)
		BUG("tar-filter archiver called with no filter defined");

	strbuf_addstr(&cmd, ar->data);
	if (args->compression_level >= 0)
		strbuf_addf(&cmd, " -%d", args->compression_level);

	argv[0] = cmd.buf;
	argv[1] = NULL;
	filter.argv = argv;
	filter.use_shell = 1;
	filter.in = -1;

	if (start_command(&filter) < 0)
		die_errno(_("unable to start '%s' filter"), argv[0]);
	close(1);
	if (dup2(filter.in, 1) < 0)
		die_errno(_("unable to redirect descriptor"));
	close(filter.in);

	r = write_tar_archive(ar, args);

	close(1);
	if (finish_command(&filter) != 0)
		die(_("'%s' filter reported error"), argv[0]);

	strbuf_release(&cmd);
	return r;
}