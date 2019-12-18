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
struct symtab {struct symtab* next; struct objfile* objfile; void* debugformat; int /*<<< orphan*/  language; int /*<<< orphan*/ * fullname; void* filename; } ;
struct objfile {struct symtab* symtabs; int /*<<< orphan*/  objfile_obstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_EXTRA_SYMTAB_INFO (struct symtab*) ; 
 int /*<<< orphan*/  deduce_language_from_filename (char*) ; 
 int /*<<< orphan*/  memset (struct symtab*,int /*<<< orphan*/ ,int) ; 
 void* obsavestring (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 

struct symtab *
allocate_symtab (char *filename, struct objfile *objfile)
{
  struct symtab *symtab;

  symtab = (struct symtab *)
    obstack_alloc (&objfile->objfile_obstack, sizeof (struct symtab));
  memset (symtab, 0, sizeof (*symtab));
  symtab->filename = obsavestring (filename, strlen (filename),
				   &objfile->objfile_obstack);
  symtab->fullname = NULL;
  symtab->language = deduce_language_from_filename (filename);
  symtab->debugformat = obsavestring ("unknown", 7,
				      &objfile->objfile_obstack);

  /* Hook it to the objfile it comes from */

  symtab->objfile = objfile;
  symtab->next = objfile->symtabs;
  objfile->symtabs = symtab;

  /* FIXME: This should go away.  It is only defined for the Z8000,
     and the Z8000 definition of this macro doesn't have anything to
     do with the now-nonexistent EXTRA_SYMTAB_INFO macro, it's just
     here for convenience.  */
#ifdef INIT_EXTRA_SYMTAB_INFO
  INIT_EXTRA_SYMTAB_INFO (symtab);
#endif

  return (symtab);
}