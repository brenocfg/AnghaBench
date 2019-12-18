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
struct strbuf {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_USING_SHELL ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* getenv (char*) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 

int cmd_main(int argc, const char **argv)
{
	const char *trash_directory = getenv("TRASH_DIRECTORY");
	struct strbuf buf = STRBUF_INIT;
	FILE *f;
	int i;
	const char *child_argv[] = { NULL, NULL };

	/* First, print all parameters into $TRASH_DIRECTORY/ssh-output */
	if (!trash_directory)
		die("Need a TRASH_DIRECTORY!");
	strbuf_addf(&buf, "%s/ssh-output", trash_directory);
	f = fopen(buf.buf, "w");
	if (!f)
		die("Could not write to %s", buf.buf);
	for (i = 0; i < argc; i++)
		fprintf(f, "%s%s", i > 0 ? " " : "", i > 0 ? argv[i] : "ssh:");
	fprintf(f, "\n");
	fclose(f);

	/* Now, evaluate the *last* parameter */
	if (argc < 2)
		return 0;
	child_argv[0] = argv[argc - 1];
	return run_command_v_opt(child_argv, RUN_USING_SHELL);
}