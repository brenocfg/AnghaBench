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
struct backtrace_command_args {char* count_exp; int show_locals; int from_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  backtrace_command_stub ; 
 char** buildargv (char*) ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_freeargv (char**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ subset_compare (char*,char*) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
backtrace_command (char *arg, int from_tty)
{
  struct cleanup *old_chain = (struct cleanup *) NULL;
  char **argv = (char **) NULL;
  int argIndicatingFullTrace = (-1), totArgLen = 0, argc = 0;
  char *argPtr = arg;
  struct backtrace_command_args btargs;

  if (arg != (char *) NULL)
    {
      int i;

      argv = buildargv (arg);
      old_chain = make_cleanup_freeargv (argv);
      argc = 0;
      for (i = 0; (argv[i] != (char *) NULL); i++)
	{
	  unsigned int j;

	  for (j = 0; (j < strlen (argv[i])); j++)
	    argv[i][j] = tolower (argv[i][j]);

	  if (argIndicatingFullTrace < 0 && subset_compare (argv[i], "full"))
	    argIndicatingFullTrace = argc;
	  else
	    {
	      argc++;
	      totArgLen += strlen (argv[i]);
	    }
	}
      totArgLen += argc;
      if (argIndicatingFullTrace >= 0)
	{
	  if (totArgLen > 0)
	    {
	      argPtr = (char *) xmalloc (totArgLen + 1);
	      if (!argPtr)
		nomem (0);
	      else
		{
		  memset (argPtr, 0, totArgLen + 1);
		  for (i = 0; (i < (argc + 1)); i++)
		    {
		      if (i != argIndicatingFullTrace)
			{
			  strcat (argPtr, argv[i]);
			  strcat (argPtr, " ");
			}
		    }
		}
	    }
	  else
	    argPtr = (char *) NULL;
	}
    }

  btargs.count_exp = argPtr;
  btargs.show_locals = (argIndicatingFullTrace >= 0);
  btargs.from_tty = from_tty;
  catch_errors (backtrace_command_stub, (char *)&btargs, "", RETURN_MASK_ERROR);

  if (argIndicatingFullTrace >= 0 && totArgLen > 0)
    xfree (argPtr);

  if (old_chain)
    do_cleanups (old_chain);
}