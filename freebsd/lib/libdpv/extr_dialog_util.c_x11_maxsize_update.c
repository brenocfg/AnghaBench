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
struct winsize {int dummy; } ;
struct TYPE_3__ {unsigned short ws_row; unsigned short ws_col; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 scalar_t__ debug ; 
 char* dialog ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_1__* maxsize ; 
 int /*<<< orphan*/  memset (void*,char,int) ; 
 scalar_t__ pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void
x11_maxsize_update(void)
{
	FILE *f = NULL;
	char *cols;
	char *cp;
	char *rows;
	char cmdbuf[LINE_MAX];
	char rbuf[LINE_MAX];

	if (maxsize == NULL) {
		if ((maxsize = malloc(sizeof(struct winsize))) == NULL)
			errx(EXIT_FAILURE, "Out of memory?!");
		memset((void *)maxsize, '\0', sizeof(struct winsize));
	}

	/* Assemble the command necessary to get X11 sizes */
	snprintf(cmdbuf, LINE_MAX, "%s --print-maxsize 2>&1", dialog);

	fflush(STDIN_FILENO); /* prevent popen(3) from seeking on stdin */

	if ((f = popen(cmdbuf, "r")) == NULL) {
		if (debug)
			warnx("WARNING! Command `%s' failed", cmdbuf);
		return;
	}

	/* Read in the line returned from Xdialog(1) */
	if ((fgets(rbuf, LINE_MAX, f) == NULL) || (pclose(f) < 0))
		return;

	/* Check for X11-related errors */
	if (strncmp(rbuf, "Xdialog: Error", 14) == 0)
		return;

	/* Parse expected output: MaxSize: YY, XXX */
	if ((rows = strchr(rbuf, ' ')) == NULL)
		return;
	if ((cols = strchr(rows, ',')) != NULL) {
		/* strtonum(3) doesn't like trailing junk */
		*(cols++) = '\0';
		if ((cp = strchr(cols, '\n')) != NULL)
			*cp = '\0';
	}

	/* Convert to unsigned short */
	maxsize->ws_row = (unsigned short)strtonum(
	    rows, 0, USHRT_MAX, (const char **)NULL);
	maxsize->ws_col = (unsigned short)strtonum(
	    cols, 0, USHRT_MAX, (const char **)NULL);
}