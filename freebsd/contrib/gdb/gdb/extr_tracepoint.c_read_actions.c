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
struct tracepoint {struct action_line* actions; } ;
struct cleanup {int dummy; } ;
struct action_line {char* action; struct action_line* next; } ;
typedef  enum actionline_type { ____Placeholder_actionline_type } actionline_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BADLINE ; 
 int END ; 
 scalar_t__ ISATTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int STEPPING ; 
 int /*<<< orphan*/  STOP_SIGNAL ; 
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 scalar_t__ event_loop_p ; 
 int /*<<< orphan*/  free_actions (struct tracepoint*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 char* gdb_readline (int /*<<< orphan*/ ) ; 
 char* gdb_readline_wrapper (char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  handle_stop_sig ; 
 int /*<<< orphan*/  immediate_quit ; 
 scalar_t__ job_control ; 
 struct cleanup* make_cleanup_free_actions (struct tracepoint*) ; 
 char* readline_hook (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stop_sig ; 
 char* stub1 (char*) ; 
 int validate_actionline (char**,struct tracepoint*) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 
 struct action_line* xmalloc (int) ; 

__attribute__((used)) static void
read_actions (struct tracepoint *t)
{
  char *line;
  char *prompt1 = "> ", *prompt2 = "  > ";
  char *prompt = prompt1;
  enum actionline_type linetype;
  extern FILE *instream;
  struct action_line *next = NULL, *temp;
  struct cleanup *old_chain;

  /* Control-C quits instantly if typed while in this loop
     since it should not wait until the user types a newline.  */
  immediate_quit++;
  /* FIXME: kettenis/20010823: Something is wrong here.  In this file
     STOP_SIGNAL is never defined.  So this code has been left out, at
     least for quite a while now.  Replacing STOP_SIGNAL with SIGTSTP
     leads to compilation failures since the variable job_control
     isn't declared.  Leave this alone for now.  */
#ifdef STOP_SIGNAL
  if (job_control)
    {
      if (event_loop_p)
	signal (STOP_SIGNAL, handle_stop_sig);
      else
	signal (STOP_SIGNAL, stop_sig);
    }
#endif
  old_chain = make_cleanup_free_actions (t);
  while (1)
    {
      /* Make sure that all output has been output.  Some machines may let
         you get away with leaving out some of the gdb_flush, but not all.  */
      wrap_here ("");
      gdb_flush (gdb_stdout);
      gdb_flush (gdb_stderr);

      if (readline_hook && instream == NULL)
	line = (*readline_hook) (prompt);
      else if (instream == stdin && ISATTY (instream))
	{
	  line = gdb_readline_wrapper (prompt);
	  if (line && *line)	/* add it to command history */
	    add_history (line);
	}
      else
	line = gdb_readline (0);

      linetype = validate_actionline (&line, t);
      if (linetype == BADLINE)
	continue;		/* already warned -- collect another line */

      temp = xmalloc (sizeof (struct action_line));
      temp->next = NULL;
      temp->action = line;

      if (next == NULL)		/* first action for this tracepoint? */
	t->actions = next = temp;
      else
	{
	  next->next = temp;
	  next = temp;
	}

      if (linetype == STEPPING)	/* begin "while-stepping" */
	{
	  if (prompt == prompt2)
	    {
	      warning ("Already processing 'while-stepping'");
	      continue;
	    }
	  else
	    prompt = prompt2;	/* change prompt for stepping actions */
	}
      else if (linetype == END)
	{
	  if (prompt == prompt2)
	    {
	      prompt = prompt1;	/* end of single-stepping actions */
	    }
	  else
	    {			/* end of actions */
	      if (t->actions->next == NULL)
		{
		  /* an "end" all by itself with no other actions means
		     this tracepoint has no actions.  Discard empty list. */
		  free_actions (t);
		}
	      break;
	    }
	}
    }
#ifdef STOP_SIGNAL
  if (job_control)
    signal (STOP_SIGNAL, SIG_DFL);
#endif
  immediate_quit--;
  discard_cleanups (old_chain);
}