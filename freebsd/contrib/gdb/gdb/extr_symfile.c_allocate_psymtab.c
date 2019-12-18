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
struct partial_symtab {struct partial_symtab* next; struct objfile* objfile; int /*<<< orphan*/ * symtab; int /*<<< orphan*/  filename; } ;
struct objfile {struct partial_symtab* psymtabs; int /*<<< orphan*/  objfile_obstack; struct partial_symtab* free_psymtabs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct partial_symtab*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obsavestring (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

struct partial_symtab *
allocate_psymtab (char *filename, struct objfile *objfile)
{
  struct partial_symtab *psymtab;

  if (objfile->free_psymtabs)
    {
      psymtab = objfile->free_psymtabs;
      objfile->free_psymtabs = psymtab->next;
    }
  else
    psymtab = (struct partial_symtab *)
      obstack_alloc (&objfile->objfile_obstack,
		     sizeof (struct partial_symtab));

  memset (psymtab, 0, sizeof (struct partial_symtab));
  psymtab->filename = obsavestring (filename, strlen (filename),
				    &objfile->objfile_obstack);
  psymtab->symtab = NULL;

  /* Prepend it to the psymtab list for the objfile it belongs to.
     Psymtabs are searched in most recent inserted -> least recent
     inserted order. */

  psymtab->objfile = objfile;
  psymtab->next = objfile->psymtabs;
  objfile->psymtabs = psymtab;
#if 0
  {
    struct partial_symtab **prev_pst;
    psymtab->objfile = objfile;
    psymtab->next = NULL;
    prev_pst = &(objfile->psymtabs);
    while ((*prev_pst) != NULL)
      prev_pst = &((*prev_pst)->next);
    (*prev_pst) = psymtab;
  }
#endif

  return (psymtab);
}