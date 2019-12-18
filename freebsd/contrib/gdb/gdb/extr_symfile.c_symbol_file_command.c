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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int OBJF_READNOW ; 
 int OBJF_USERLOADED ; 
 char** buildargv (char*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct cleanup* make_cleanup_freeargv (char**) ; 
 int /*<<< orphan*/  nomem (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  symbol_file_add_main_1 (char*,int,int) ; 
 int /*<<< orphan*/  symbol_file_clear (int) ; 

void
symbol_file_command (char *args, int from_tty)
{
  char **argv;
  char *name = NULL;
  struct cleanup *cleanups;
  int flags = OBJF_USERLOADED;

  dont_repeat ();

  if (args == NULL)
    {
      symbol_file_clear (from_tty);
    }
  else
    {
      if ((argv = buildargv (args)) == NULL)
	{
	  nomem (0);
	}
      cleanups = make_cleanup_freeargv (argv);
      while (*argv != NULL)
	{
	  if (strcmp (*argv, "-readnow") == 0)
	    flags |= OBJF_READNOW;
	  else if (**argv == '-')
	    error ("unknown option `%s'", *argv);
	  else
	    {
	      name = *argv;
	      
	      symbol_file_add_main_1 (name, from_tty, flags);
	    }
	  argv++;
	}

      if (name == NULL)
	{
	  error ("no symbol file name was specified");
	}
      do_cleanups (cleanups);
    }
}