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
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  all_variables ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_variables (char const*) ; 
 int /*<<< orphan*/  print_variables (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  subst_from_stdin () ; 
 int /*<<< orphan*/  trace2_cmd_name (char*) ; 

int
cmd_main (int argc, const char *argv[])
{
  /* Default values for command line options.  */
  /* unsigned short int show_variables = 0; */

  trace2_cmd_name("sh-i18n--envsubst");

  switch (argc)
	{
	case 1:
	  error ("we won't substitute all variables on stdin for you");
	  break;
	  /*
	  all_variables = 1;
      subst_from_stdin ();
	  */
	case 2:
	  /* echo '$foo and $bar' | git sh-i18n--envsubst --variables '$foo and $bar' */
	  all_variables = 0;
	  note_variables (argv[1]);
      subst_from_stdin ();
	  break;
	case 3:
	  /* git sh-i18n--envsubst --variables '$foo and $bar' */
	  if (strcmp(argv[1], "--variables"))
		error ("first argument must be --variables when two are given");
	  /* show_variables = 1; */
      print_variables (argv[2]);
	  break;
	default:
	  error ("too many arguments");
	  break;
	}

  /* Close standard error.  This is simpler than fwriteerror_no_ebadf, because
     upon failure we don't need an errno - all we can do at this point is to
     set an exit status.  */
  errno = 0;
  if (ferror (stderr) || fflush (stderr))
    {
      fclose (stderr);
      exit (EXIT_FAILURE);
    }
  if (fclose (stderr) && errno != EBADF)
    exit (EXIT_FAILURE);

  exit (EXIT_SUCCESS);
}