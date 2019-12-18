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

/* Variables and functions */
 char* DEFAULT_EDITOR ; 
 int /*<<< orphan*/  EX_CANTCREAT ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  cleanup_editfile () ; 
 int /*<<< orphan*/ * edit_file ; 
 char* edit_path ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  modepage_read (int /*<<< orphan*/ *) ; 
 int modepage_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strlen (char const*) ; 
 int system (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
modepage_edit(void)
{
	const char *editor;
	char *commandline;
	int fd;
	int written;

	if (!isatty(fileno(stdin))) {
		/* Not a tty, read changes from stdin. */
		modepage_read(stdin);
		return;
	}

	/* Lookup editor to invoke. */
	if ((editor = getenv("EDITOR")) == NULL)
		editor = DEFAULT_EDITOR;

	/* Create temp file for editor to modify. */
	if ((fd = mkstemp(edit_path)) == -1)
		errx(EX_CANTCREAT, "mkstemp failed");

	atexit(cleanup_editfile);

	if ((edit_file = fdopen(fd, "w")) == NULL)
		err(EX_NOINPUT, "%s", edit_path);

	written = modepage_write(edit_file, 1);

	fclose(edit_file);
	edit_file = NULL;

	if (written == 0) {
		warnx("no editable entries");
		cleanup_editfile();
		return;
	}

	/*
	 * Allocate memory to hold the command line (the 2 extra characters
	 * are to hold the argument separator (a space), and the terminating
	 * null character.
	 */
	commandline = malloc(strlen(editor) + strlen(edit_path) + 2);
	if (commandline == NULL)
		err(EX_OSERR, NULL);
	sprintf(commandline, "%s %s", editor, edit_path);

	/* Invoke the editor on the temp file. */
	if (system(commandline) == -1)
		err(EX_UNAVAILABLE, "could not invoke %s", editor);
	free(commandline);

	if ((edit_file = fopen(edit_path, "r")) == NULL)
		err(EX_NOINPUT, "%s", edit_path);

	/* Read any changes made to the temp file. */
	modepage_read(edit_file);

	cleanup_editfile();
}