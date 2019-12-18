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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* PIDFILE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
send_disconnect(const char *ifnam)
{
	char pidfile[128];
	FILE *fp;
	pid_t pid;
	int n;

	snprintf(pidfile, 127, PIDFILE, ifnam);
	fp = fopen(pidfile, "r");
	if (fp == NULL) {
		warn("Cannot open %s", pidfile);
		return;
	}

	n = fscanf(fp, "%d", &pid);
	fclose(fp);
	if (n != 1) {
		warnx("unable to read daemon pid");
		return;
	}
#ifdef DEBUG
	fprintf(stderr, "Sending SIGTERM to %d\n", pid);
#endif
	kill(pid, SIGTERM);
}