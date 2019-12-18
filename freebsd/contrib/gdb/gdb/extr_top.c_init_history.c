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
 int atoi (char*) ; 
 scalar_t__ concat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_directory ; 
 char* getenv (char*) ; 
 scalar_t__ history_filename ; 
 int history_size ; 
 int /*<<< orphan*/  read_history (scalar_t__) ; 
 scalar_t__ savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stifle_history (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
init_history (void)
{
  char *tmpenv;

  tmpenv = getenv ("HISTSIZE");
  if (tmpenv)
    history_size = atoi (tmpenv);
  else if (!history_size)
    history_size = 256;

  stifle_history (history_size);

  tmpenv = getenv ("GDBHISTFILE");
  if (tmpenv)
    history_filename = savestring (tmpenv, strlen (tmpenv));
  else if (!history_filename)
    {
      /* We include the current directory so that if the user changes
         directories the file written will be the same as the one
         that was read.  */
#ifdef __MSDOS__
      /* No leading dots in file names are allowed on MSDOS.  */
      history_filename = concat (current_directory, "/_gdb_history", NULL);
#else
      history_filename = concat (current_directory, "/.gdb_history", NULL);
#endif
    }
  read_history (history_filename);
}