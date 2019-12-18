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
struct symtab {int free_code; TYPE_1__* objfile; struct symtab* debugformat; struct symtab* fullname; struct symtab* line_charpos; int /*<<< orphan*/  (* free_func ) (struct symtab*) ;} ;
struct blockvector {int free_code; TYPE_1__* objfile; struct blockvector* debugformat; struct blockvector* fullname; struct blockvector* line_charpos; int /*<<< orphan*/  (* free_func ) (struct symtab*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  md; } ;

/* Variables and functions */
 struct symtab* BLOCKVECTOR (struct symtab*) ; 
 int /*<<< orphan*/  BLOCKVECTOR_BLOCK (struct symtab*,int) ; 
 int BLOCKVECTOR_NBLOCKS (struct symtab*) ; 
 struct symtab* LINETABLE (struct symtab*) ; 
#define  free_contents 130 
#define  free_linetable 129 
#define  free_nothing 128 
 int /*<<< orphan*/  free_symtab_block (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct symtab*) ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,struct symtab*) ; 

void
free_symtab (struct symtab *s)
{
  int i, n;
  struct blockvector *bv;

  switch (s->free_code)
    {
    case free_nothing:
      /* All the contents are part of a big block of memory (an obstack),
         and some other symtab is in charge of freeing that block.
         Therefore, do nothing.  */
      break;

    case free_contents:
      /* Here all the contents were malloc'ed structure by structure
         and must be freed that way.  */
      /* First free the blocks (and their symbols.  */
      bv = BLOCKVECTOR (s);
      n = BLOCKVECTOR_NBLOCKS (bv);
      for (i = 0; i < n; i++)
	free_symtab_block (s->objfile, BLOCKVECTOR_BLOCK (bv, i));
      /* Free the blockvector itself.  */
      xmfree (s->objfile->md, bv);
      /* Also free the linetable.  */

    case free_linetable:
      /* Everything will be freed either by our `free_func'
         or by some other symtab, except for our linetable.
         Free that now.  */
      if (LINETABLE (s))
	xmfree (s->objfile->md, LINETABLE (s));
      break;
    }

  /* If there is a single block of memory to free, free it.  */
  if (s->free_func != NULL)
    s->free_func (s);

  /* Free source-related stuff */
  if (s->line_charpos != NULL)
    xmfree (s->objfile->md, s->line_charpos);
  if (s->fullname != NULL)
    xmfree (s->objfile->md, s->fullname);
  if (s->debugformat != NULL)
    xmfree (s->objfile->md, s->debugformat);
  xmfree (s->objfile->md, s);
}