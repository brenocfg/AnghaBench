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
typedef  int /*<<< orphan*/  cmdbuf ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int MAX_C_NAME ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ get_line (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getit (int,char**,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ restart_point ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ttyout ; 

void
fget(int argc, char *argv[])
{
	const char *gmode;
	FILE	*fp;
	char	buf[MAXPATHLEN], cmdbuf[MAX_C_NAME];

	if (argc != 2) {
		UPRINTF("usage: %s localfile\n", argv[0]);
		code = -1;
		return;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(ttyout, "Can't open source file %s\n", argv[1]);
		code = -1;
		return;
	}

	(void)strlcpy(cmdbuf, "get", sizeof(cmdbuf));
	argv[0] = cmdbuf;
	gmode = restart_point ? "r+" : "w";

	while (get_line(fp, buf, sizeof(buf), NULL) >= 0) {
		if (buf[0] == '\0')
			continue;
		argv[1] = buf;
		(void)getit(argc, argv, 0, gmode);
	}
	fclose(fp);
}