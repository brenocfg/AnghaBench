#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ frow; scalar_t__ fcol; struct TYPE_6__* snext; struct TYPE_6__* sprev; } ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static FIELD *
Insert_Field_By_Position(FIELD *newfield, FIELD *head)
{
  FIELD *current, *newhead;

  assert(newfield);

  if (!head)
    {				/* empty list is trivial */
      newhead = newfield->snext = newfield->sprev = newfield;
    }
  else
    {
      newhead = current = head;
      while ((current->frow < newfield->frow) ||
	     ((current->frow == newfield->frow) &&
	      (current->fcol < newfield->fcol)))
	{
	  current = current->snext;
	  if (current == head)
	    {			/* We cycled through. Reset head to indicate that */
	      head = (FIELD *)0;
	      break;
	    }
	}
      /* we leave the loop with current pointing to the field after newfield */
      newfield->snext = current;
      newfield->sprev = current->sprev;
      newfield->snext->sprev = newfield;
      newfield->sprev->snext = newfield;
      if (current == head)
	newhead = newfield;
    }
  return (newhead);
}