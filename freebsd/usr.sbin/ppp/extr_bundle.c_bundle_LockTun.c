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
struct bundle {int unit; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * ID0fopen (char*,char*) ; 
 int /*<<< orphan*/  LogERROR ; 
 int PATH_MAX ; 
 char* _PATH_VARRUN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
bundle_LockTun(struct bundle *bundle)
{
  FILE *lockfile;
  char pidfile[PATH_MAX];

  snprintf(pidfile, sizeof pidfile, "%stun%d.pid", _PATH_VARRUN, bundle->unit);
  lockfile = ID0fopen(pidfile, "w");
  if (lockfile != NULL) {
    fprintf(lockfile, "%d\n", (int)getpid());
    fclose(lockfile);
  } else
    log_Printf(LogERROR, "Warning: Can't create %s: %s\n",
               pidfile, strerror(errno));
}