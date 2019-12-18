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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  kprintf (char*,char const*) ; 

void save_pid (const pid_t pid, const char *pid_file) {
  FILE *fp;
  if (pid_file == NULL)
    return;

  if ((fp = fopen(pid_file, "w")) == NULL) {
    kprintf ("Could not open the pid file %s for writing\n", pid_file);
    return;
  }

  fprintf(fp,"%ld\n", (long)pid);
  if (fclose(fp) == -1) {
    kprintf ("Could not close the pid file %s.\n", pid_file);
    return;
  }
}