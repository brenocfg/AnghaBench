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
 char* PREFIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 char* SUFFIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  after_char_processing_hook () ; 
 scalar_t__ async_command_editing_p ; 
 int catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_gdb_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_do_one_event ; 
 char* get_prompt () ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  rl_callback_handler_install (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ tui_active ; 
 int /*<<< orphan*/  tui_old_uiout ; 
 int /*<<< orphan*/  tui_out ; 
 int /*<<< orphan*/  uiout ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
tui_command_loop (void *data)
{
  int length;
  char *a_prompt;
  char *gdb_prompt = get_prompt ();

  /* If we are using readline, set things up and display the first
     prompt, otherwise just print the prompt.  */
  if (async_command_editing_p)
    {
      /* Tell readline what the prompt to display is and what function
         it will need to call after a whole line is read. This also
         displays the first prompt.  */
      length = strlen (PREFIX (0)) + strlen (gdb_prompt) + strlen (SUFFIX (0)) + 1;
      a_prompt = (char *) xmalloc (length);
      strcpy (a_prompt, PREFIX (0));
      strcat (a_prompt, gdb_prompt);
      strcat (a_prompt, SUFFIX (0));
      rl_callback_handler_install (a_prompt, input_handler);
    }
  else
    display_gdb_prompt (0);

  /* Loop until there is nothing to do. This is the entry point to the
     event loop engine. gdb_do_one_event, called via catch_errors()
     will process one event for each invocation.  It blocks waits for
     an event and then processes it.  >0 when an event is processed, 0
     when catch_errors() caught an error and <0 when there are no
     longer any event sources registered.  */
  while (1)
    {
      int result = catch_errors (gdb_do_one_event, 0, "", RETURN_MASK_ALL);
      if (result < 0)
	break;

      /* Update gdb output according to TUI mode.  Since catch_errors
         preserves the uiout from changing, this must be done at top
         level of event loop.  */
      if (tui_active)
        uiout = tui_out;
      else
        uiout = tui_old_uiout;
      
      if (result == 0)
	{
	  /* FIXME: this should really be a call to a hook that is
	     interface specific, because interfaces can display the
	     prompt in their own way.  */
	  display_gdb_prompt (0);
	  /* This call looks bizarre, but it is required.  If the user
	     entered a command that caused an error,
	     after_char_processing_hook won't be called from
	     rl_callback_read_char_wrapper.  Using a cleanup there
	     won't work, since we want this function to be called
	     after a new prompt is printed.  */
	  if (after_char_processing_hook)
	    (*after_char_processing_hook) ();
	  /* Maybe better to set a flag to be checked somewhere as to
	     whether display the prompt or not.  */
	}
    }

  /* We are done with the event loop. There are no more event sources
     to listen to.  So we exit GDB.  */
  return;
}