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
struct thread_info {int /*<<< orphan*/  num; int /*<<< orphan*/  ptid; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  execute_command (char*,int) ; 
 struct thread_info* find_thread_id (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  isalpha (char) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,void*) ; 
 struct cleanup* make_cleanup_restore_current_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  switch_to_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_tid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_alive (struct thread_info*) ; 
 int /*<<< orphan*/  warning (char*,int) ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
thread_apply_command (char *tidlist, int from_tty)
{
  char *cmd;
  char *p;
  struct cleanup *old_chain;
  struct cleanup *saved_cmd_cleanup_chain;
  char *saved_cmd;

  if (tidlist == NULL || *tidlist == '\000')
    error ("Please specify a thread ID list");

  for (cmd = tidlist; *cmd != '\000' && !isalpha (*cmd); cmd++);

  if (*cmd == '\000')
    error ("Please specify a command following the thread ID list");

  old_chain = make_cleanup_restore_current_thread (inferior_ptid);

  /* Save a copy of the command in case it is clobbered by
     execute_command */
  saved_cmd = xstrdup (cmd);
  saved_cmd_cleanup_chain = make_cleanup (xfree, (void *) saved_cmd);
  while (tidlist < cmd)
    {
      struct thread_info *tp;
      int start, end;

      start = strtol (tidlist, &p, 10);
      if (p == tidlist)
	error ("Error parsing %s", tidlist);
      tidlist = p;

      while (*tidlist == ' ' || *tidlist == '\t')
	tidlist++;

      if (*tidlist == '-')	/* Got a range of IDs? */
	{
	  tidlist++;		/* Skip the - */
	  end = strtol (tidlist, &p, 10);
	  if (p == tidlist)
	    error ("Error parsing %s", tidlist);
	  tidlist = p;

	  while (*tidlist == ' ' || *tidlist == '\t')
	    tidlist++;
	}
      else
	end = start;

      for (; start <= end; start++)
	{
	  tp = find_thread_id (start);

	  if (!tp)
	    warning ("Unknown thread %d.", start);
	  else if (!thread_alive (tp))
	    warning ("Thread %d has terminated.", start);
	  else
	    {
	      switch_to_thread (tp->ptid);
#ifdef HPUXHPPA
	      printf_filtered ("\nThread %d (%s):\n", tp->num,
			       target_tid_to_str (inferior_ptid));
#else
	      printf_filtered ("\nThread %d (%s):\n", tp->num,
			       target_pid_to_str (inferior_ptid));
#endif
	      execute_command (cmd, from_tty);
	      strcpy (cmd, saved_cmd);	/* Restore exact command used previously */
	    }
	}
    }

  do_cleanups (saved_cmd_cleanup_chain);
  do_cleanups (old_chain);
}