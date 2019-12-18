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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  dologout (int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftpd_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftpd_popen (char*,char*,int,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lreply (int,char*,char*) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reply (int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/ * stdout ; 

void
statfilecmd(char *filename)
{
	FILE *fin;
	int c;
	char line[LINE_MAX];

	snprintf(line, sizeof(line), "/bin/ls -la -- %s", filename);
	fin = ftpd_popen(line, "r", 1, 0);
	lreply(211, "status of %s:", filename);
	while ((c = getc(fin)) != EOF) {
		if (c == '\n') {
			if (ferror(stdout)){
				perror_reply(421, "control connection");
				ftpd_pclose(fin);
				dologout(1);
				/* NOTREACHED */
			}
			if (ferror(fin)) {
				perror_reply(551, filename);
				ftpd_pclose(fin);
				return;
			}
			putc('\r', stdout);
		}
		putc(c, stdout);
	}
	ftpd_pclose(fin);
	reply(211, "End of Status");
}