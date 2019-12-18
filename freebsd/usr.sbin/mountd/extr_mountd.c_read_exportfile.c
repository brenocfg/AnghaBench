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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ ** exnames ; 
 int /*<<< orphan*/ * exp_file ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_exportlist_one (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
read_exportfile(int passno)
{
	int done, i;

	/*
	 * Read in the exports file and build the list, calling
	 * nmount() as we go along to push the export rules into the kernel.
	 */
	done = 0;
	for (i = 0; exnames[i] != NULL; i++) {
		if (debug)
			warnx("reading exports from %s", exnames[i]);
		if ((exp_file = fopen(exnames[i], "r")) == NULL) {
			syslog(LOG_WARNING, "can't open %s", exnames[i]);
			continue;
		}
		get_exportlist_one(passno);
		fclose(exp_file);
		done++;
	}
	if (done == 0) {
		syslog(LOG_ERR, "can't open any exports file");
		exit(2);
	}
}