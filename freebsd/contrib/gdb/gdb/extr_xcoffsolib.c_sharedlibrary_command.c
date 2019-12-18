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
struct vmap {char* name; char* member; scalar_t__ loaded; struct vmap* nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* re_comp (char*) ; 
 scalar_t__ re_exec (char*) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 struct vmap* vmap ; 
 scalar_t__ vmap_add_symbols (struct vmap*) ; 
 int /*<<< orphan*/  xcoff_relocate_symtab (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sharedlibrary_command (char *pattern, int from_tty)
{
  dont_repeat ();

  /* Check for new shared libraries loaded with load ().  */
  if (! ptid_equal (inferior_ptid, null_ptid))
    xcoff_relocate_symtab (PIDGET (inferior_ptid));

  if (pattern)
    {
      char *re_err = re_comp (pattern);

      if (re_err)
	error ("Invalid regexp: %s", re_err);
    }

  /* Walk the list of currently loaded shared libraries, and read
     symbols for any that match the pattern --- or any whose symbols
     aren't already loaded, if no pattern was given.  */
  {
    int any_matches = 0;
    int loaded_any_symbols = 0;
    struct vmap *vp = vmap;

    if (!vp)
      return;

    /* skip over the first vmap, it is the main program, always loaded. */
    for (vp = vp->nxt; vp; vp = vp->nxt)
      if (! pattern
	    || re_exec (vp->name)
	    || (*vp->member && re_exec (vp->member)))
	{
	  any_matches = 1;

	  if (vp->loaded)
	    {
	      if (from_tty)
		printf_unfiltered ("Symbols already loaded for %s\n",
				   vp->name);
	    }
	  else
	    {
	      if (vmap_add_symbols (vp))
		loaded_any_symbols = 1;
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
      }
  }
}