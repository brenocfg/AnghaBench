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
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  forget_cached_source_info () ; 
 int /*<<< orphan*/  init_source_path () ; 
 int /*<<< orphan*/ * last_source_visited ; 
 int /*<<< orphan*/  mod_path (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  show_directories (char*,int) ; 
 int /*<<< orphan*/  source_path ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

void
directory_command (char *dirname, int from_tty)
{
  dont_repeat ();
  /* FIXME, this goes to "delete dir"... */
  if (dirname == 0)
    {
      if (from_tty && query ("Reinitialize source path to empty? "))
	{
	  xfree (source_path);
	  init_source_path ();
	}
    }
  else
    {
      mod_path (dirname, &source_path);
      last_source_visited = NULL;
    }
  if (from_tty)
    show_directories ((char *) 0, from_tty);
  forget_cached_source_info ();
}