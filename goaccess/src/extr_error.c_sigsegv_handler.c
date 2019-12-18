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
 char* ERR_PLEASE_REPORT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* GO_VERSION ; 
 int TRACE_SIZE ; 
 size_t backtrace (void**,int) ; 
 char** backtrace_symbols (void**,size_t) ; 
 int /*<<< orphan*/  dump_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int getpid () ; 
 int /*<<< orphan*/ * stderr ; 

void
sigsegv_handler (int sig)
{
  FILE *fp = stderr;
  int pid = getpid ();

#if defined(__GLIBC__)
  char **messages;
  size_t size, i;
  void *trace_stack[TRACE_SIZE];
#endif

  (void) endwin ();
  fprintf (fp, "\n");
  fprintf (fp, "==%d== GoAccess %s crashed by Sig %d\n", pid, GO_VERSION, sig);
  fprintf (fp, "==%d==\n", pid);

  dump_struct (fp);

#if defined(__GLIBC__)
  size = backtrace (trace_stack, TRACE_SIZE);
  messages = backtrace_symbols (trace_stack, size);

  fprintf (fp, "==%d== STACK TRACE:\n", pid);
  fprintf (fp, "==%d==\n", pid);

  for (i = 0; i < size; i++)
    fprintf (fp, "==%d== %zu %s\n", pid, i, messages[i]);
#endif

  fprintf (fp, "==%d==\n", pid);
  fprintf (fp, "==%d== %s:\n", pid, ERR_PLEASE_REPORT);
  fprintf (fp, "==%d== https://github.com/allinurl/goaccess/issues\n\n", pid);
  exit (EXIT_FAILURE);
}