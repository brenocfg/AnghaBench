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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getpid () ; 
 scalar_t__ pidfile ; 
 int /*<<< orphan*/  remove_pidfile () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void write_pidfile(void)
{
	FILE *f;
	if (pidfile) {
		remove_pidfile();
		f = fopen(pidfile, "w");
		if (f) {
			fprintf(f, "%d\n", getpid());
			fclose(f);
		} else {
			syslog(LOG_ERR, "Failed to write pidfile : %s\n",
				pidfile);
			exit(errno);
		}
	}
}