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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  target_files_info () ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_kill () ; 
 int /*<<< orphan*/  tcomplain () ; 

__attribute__((used)) static void
kill_or_be_killed (int from_tty)
{
  if (target_has_execution)
    {
      printf_unfiltered ("You are already running a program:\n");
      target_files_info ();
      if (query ("Kill it? "))
	{
	  target_kill ();
	  if (target_has_execution)
	    error ("Killing the program did not help.");
	  return;
	}
      else
	{
	  error ("Program not killed.");
	}
    }
  tcomplain ();
}