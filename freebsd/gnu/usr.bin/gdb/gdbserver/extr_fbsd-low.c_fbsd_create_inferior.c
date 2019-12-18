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
 int /*<<< orphan*/  PT_TRACE_ME ; 
 int /*<<< orphan*/  _exit (int) ; 
 void* add_process (int) ; 
 int /*<<< orphan*/  add_thread (int,void*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int vfork () ; 

__attribute__((used)) static int
fbsd_create_inferior (char *program, char **allargs)
{
  void *new_process;
  int pid;

  pid = vfork ();
  if (pid < 0)
    perror_with_name ("vfork");

  if (pid == 0)
    {
      ptrace (PT_TRACE_ME, 0, 0, 0);

      setpgid (0, 0);

      execv (program, allargs);

      fprintf (stderr, "Cannot exec %s: %s.\n", program,
	       strerror (errno));
      fflush (stderr);
      _exit (0177);
    }

  new_process = add_process (pid);
  add_thread (pid, new_process);

  return pid;
}