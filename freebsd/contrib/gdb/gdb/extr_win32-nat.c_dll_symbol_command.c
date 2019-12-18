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
 int OBJF_SHARED ; 
 int OBJF_USERLOADED ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  safe_symbol_file_add (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void
dll_symbol_command (char *args, int from_tty)
{
  int n;
  dont_repeat ();

  if (args == NULL)
    error ("dll-symbols requires a file name");

  n = strlen (args);
  if (n > 4 && strcasecmp (args + n - 4, ".dll") != 0)
    {
      char *newargs = (char *) alloca (n + 4 + 1);
      strcpy (newargs, args);
      strcat (newargs, ".dll");
      args = newargs;
    }

  safe_symbol_file_add (args, from_tty, NULL, 0, OBJF_SHARED | OBJF_USERLOADED);
}