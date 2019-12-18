#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct partial_symtab {int number_of_dependencies; struct partial_symtab** dependencies; struct partial_symtab* next; TYPE_1__* objfile; } ;
struct TYPE_2__ {struct partial_symtab* psymtabs; } ;

/* Variables and functions */

__attribute__((used)) static void
cashier_psymtab (struct partial_symtab *pst)
{
  struct partial_symtab *ps, *pprev = NULL;
  int i;

  /* Find its previous psymtab in the chain */
  for (ps = pst->objfile->psymtabs; ps; ps = ps->next)
    {
      if (ps == pst)
	break;
      pprev = ps;
    }

  if (ps)
    {
      /* Unhook it from the chain.  */
      if (ps == pst->objfile->psymtabs)
	pst->objfile->psymtabs = ps->next;
      else
	pprev->next = ps->next;

      /* FIXME, we can't conveniently deallocate the entries in the
         partial_symbol lists (global_psymbols/static_psymbols) that
         this psymtab points to.  These just take up space until all
         the psymtabs are reclaimed.  Ditto the dependencies list and
         filename, which are all in the objfile_obstack.  */

      /* We need to cashier any psymtab that has this one as a dependency... */
    again:
      for (ps = pst->objfile->psymtabs; ps; ps = ps->next)
	{
	  for (i = 0; i < ps->number_of_dependencies; i++)
	    {
	      if (ps->dependencies[i] == pst)
		{
		  cashier_psymtab (ps);
		  goto again;	/* Must restart, chain has been munged. */
		}
	    }
	}
    }
}