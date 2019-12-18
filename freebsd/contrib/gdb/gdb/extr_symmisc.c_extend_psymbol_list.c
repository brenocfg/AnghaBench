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
struct psymbol_allocation_list {int size; struct partial_symbol** list; struct partial_symbol** next; } ;
struct partial_symbol {int dummy; } ;
struct objfile {int /*<<< orphan*/  md; } ;

/* Variables and functions */
 scalar_t__ xmmalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmrealloc (int /*<<< orphan*/ ,char*,int) ; 

void
extend_psymbol_list (struct psymbol_allocation_list *listp,
		     struct objfile *objfile)
{
  int new_size;
  if (listp->size == 0)
    {
      new_size = 255;
      listp->list = (struct partial_symbol **)
	xmmalloc (objfile->md, new_size * sizeof (struct partial_symbol *));
    }
  else
    {
      new_size = listp->size * 2;
      listp->list = (struct partial_symbol **)
	xmrealloc (objfile->md, (char *) listp->list,
		   new_size * sizeof (struct partial_symbol *));
    }
  /* Next assumes we only went one over.  Should be good if
     program works correctly */
  listp->next = listp->list + listp->size;
  listp->size = new_size;
}