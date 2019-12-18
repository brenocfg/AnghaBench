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
struct target_ops {int dummy; } ;
struct so_list {char* so_name; int symbols_loaded; struct so_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  TARGET_SO_SPECIAL_SYMBOL_HANDLING () ; 
 scalar_t__ catch_errors (int /*<<< orphan*/ ,struct so_list*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 char* re_comp (char*) ; 
 scalar_t__ re_exec (char*) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 struct so_list* so_list_head ; 
 int /*<<< orphan*/  symbol_add_stub ; 
 int /*<<< orphan*/  update_solib_list (int,struct target_ops*) ; 

void
solib_add (char *pattern, int from_tty, struct target_ops *target, int readsyms)
{
  struct so_list *gdb;

  if (pattern)
    {
      char *re_err = re_comp (pattern);

      if (re_err)
	error ("Invalid regexp: %s", re_err);
    }

  update_solib_list (from_tty, target);

  /* Walk the list of currently loaded shared libraries, and read
     symbols for any that match the pattern --- or any whose symbols
     aren't already loaded, if no pattern was given.  */
  {
    int any_matches = 0;
    int loaded_any_symbols = 0;

    for (gdb = so_list_head; gdb; gdb = gdb->next)
      if (! pattern || re_exec (gdb->so_name))
	{
	  any_matches = 1;

	  if (gdb->symbols_loaded)
	    {
	      if (from_tty)
		printf_unfiltered ("Symbols already loaded for %s\n",
				   gdb->so_name);
	    }
	  else if (readsyms)
	    {
	      if (catch_errors
		  (symbol_add_stub, gdb,
		   "Error while reading shared library symbols:\n",
		   RETURN_MASK_ALL))
		{
		  if (from_tty)
		    printf_unfiltered ("Loaded symbols for %s\n",
				       gdb->so_name);
		  gdb->symbols_loaded = 1;
		  loaded_any_symbols = 1;
		}
	    }
	}

    if (from_tty && pattern && ! any_matches)
      printf_unfiltered
	("No loaded shared libraries match the pattern `%s'.\n", pattern);

    if (loaded_any_symbols)
      {
	/* Getting new symbols may change our opinion about what is
	   frameless.  */
	reinit_frame_cache ();

	TARGET_SO_SPECIAL_SYMBOL_HANDLING ();
      }
  }
}