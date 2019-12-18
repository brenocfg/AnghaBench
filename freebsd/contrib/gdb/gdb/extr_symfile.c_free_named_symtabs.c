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
struct symtab {struct symtab* next; int /*<<< orphan*/  filename; } ;
struct partial_symtab {int /*<<< orphan*/  filename; struct partial_symtab* next; } ;
struct blockvector {int dummy; } ;

/* Variables and functions */
 struct blockvector* BLOCKVECTOR (struct symtab*) ; 
 int /*<<< orphan*/  BLOCKVECTOR_BLOCK (struct blockvector*,int /*<<< orphan*/ ) ; 
 int BLOCKVECTOR_NBLOCKS (struct blockvector*) ; 
 scalar_t__ BLOCK_NSYMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_BLOCK ; 
 int /*<<< orphan*/  STATIC_BLOCK ; 
 int /*<<< orphan*/  cashier_psymtab (struct partial_symtab*) ; 
 int /*<<< orphan*/  clear_symtab_users_once ; 
 int /*<<< orphan*/  clear_symtab_users_queued ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free_symtab (struct symtab*) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct partial_symtab* partial_symtab_list ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_reloading ; 
 int /*<<< orphan*/  symfile_complaints ; 
 struct symtab* symtab_list ; 

int
free_named_symtabs (char *name)
{
#if 0
  /* FIXME:  With the new method of each objfile having it's own
     psymtab list, this function needs serious rethinking.  In particular,
     why was it ever necessary to toss psymtabs with specific compilation
     unit filenames, as opposed to all psymtabs from a particular symbol
     file?  -- fnf
     Well, the answer is that some systems permit reloading of particular
     compilation units.  We want to blow away any old info about these
     compilation units, regardless of which objfiles they arrived in. --gnu.  */

  struct symtab *s;
  struct symtab *prev;
  struct partial_symtab *ps;
  struct blockvector *bv;
  int blewit = 0;

  /* We only wack things if the symbol-reload switch is set.  */
  if (!symbol_reloading)
    return 0;

  /* Some symbol formats have trouble providing file names... */
  if (name == 0 || *name == '\0')
    return 0;

  /* Look for a psymtab with the specified name.  */

again2:
  for (ps = partial_symtab_list; ps; ps = ps->next)
    {
      if (strcmp (name, ps->filename) == 0)
	{
	  cashier_psymtab (ps);	/* Blow it away...and its little dog, too.  */
	  goto again2;		/* Must restart, chain has been munged */
	}
    }

  /* Look for a symtab with the specified name.  */

  for (s = symtab_list; s; s = s->next)
    {
      if (strcmp (name, s->filename) == 0)
	break;
      prev = s;
    }

  if (s)
    {
      if (s == symtab_list)
	symtab_list = s->next;
      else
	prev->next = s->next;

      /* For now, queue a delete for all breakpoints, displays, etc., whether
         or not they depend on the symtab being freed.  This should be
         changed so that only those data structures affected are deleted.  */

      /* But don't delete anything if the symtab is empty.
         This test is necessary due to a bug in "dbxread.c" that
         causes empty symtabs to be created for N_SO symbols that
         contain the pathname of the object file.  (This problem
         has been fixed in GDB 3.9x).  */

      bv = BLOCKVECTOR (s);
      if (BLOCKVECTOR_NBLOCKS (bv) > 2
	  || BLOCK_NSYMS (BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK))
	  || BLOCK_NSYMS (BLOCKVECTOR_BLOCK (bv, STATIC_BLOCK)))
	{
	  complaint (&symfile_complaints, "Replacing old symbols for `%s'",
		     name);
	  clear_symtab_users_queued++;
	  make_cleanup (clear_symtab_users_once, 0);
	  blewit = 1;
	}
      else
	{
	  complaint (&symfile_complaints, "Empty symbol table found for `%s'",
		     name);
	}

      free_symtab (s);
    }
  else
    {
      /* It is still possible that some breakpoints will be affected
         even though no symtab was found, since the file might have
         been compiled without debugging, and hence not be associated
         with a symtab.  In order to handle this correctly, we would need
         to keep a list of text address ranges for undebuggable files.
         For now, we do nothing, since this is a fairly obscure case.  */
      ;
    }

  /* FIXME, what about the minimal symbol table? */
  return blewit;
#else
  return (0);
#endif
}