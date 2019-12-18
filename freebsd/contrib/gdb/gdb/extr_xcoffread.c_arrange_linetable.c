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
struct linetable_entry {int line; int /*<<< orphan*/  pc; } ;
struct linetable {int nitems; TYPE_1__* item; } ;
struct TYPE_2__ {scalar_t__ line; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int NUM_OF_FUNCTIONS ; 
 int /*<<< orphan*/  compare_lte ; 
 int /*<<< orphan*/  qsort (struct linetable_entry*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct linetable_entry*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (struct linetable_entry*,int) ; 

__attribute__((used)) static struct linetable *
arrange_linetable (struct linetable *oldLineTb)
{
  int ii, jj, newline,		/* new line count */
    function_count;		/* # of functions */

  struct linetable_entry *fentry;	/* function entry vector */
  int fentry_size;		/* # of function entries */
  struct linetable *newLineTb;	/* new line table */

#define NUM_OF_FUNCTIONS 20

  fentry_size = NUM_OF_FUNCTIONS;
  fentry = (struct linetable_entry *)
    xmalloc (fentry_size * sizeof (struct linetable_entry));

  for (function_count = 0, ii = 0; ii < oldLineTb->nitems; ++ii)
    {

      if (oldLineTb->item[ii].line == 0)
	{			/* function entry found. */

	  if (function_count >= fentry_size)
	    {			/* make sure you have room. */
	      fentry_size *= 2;
	      fentry = (struct linetable_entry *)
		xrealloc (fentry, fentry_size * sizeof (struct linetable_entry));
	    }
	  fentry[function_count].line = ii;
	  fentry[function_count].pc = oldLineTb->item[ii].pc;
	  ++function_count;
	}
    }

  if (function_count == 0)
    {
      xfree (fentry);
      return oldLineTb;
    }
  else if (function_count > 1)
    qsort (fentry, function_count, sizeof (struct linetable_entry), compare_lte);

  /* allocate a new line table. */
  newLineTb = (struct linetable *)
    xmalloc
    (sizeof (struct linetable) +
    (oldLineTb->nitems - function_count) * sizeof (struct linetable_entry));

  /* if line table does not start with a function beginning, copy up until
     a function begin. */

  newline = 0;
  if (oldLineTb->item[0].line != 0)
    for (newline = 0;
    newline < oldLineTb->nitems && oldLineTb->item[newline].line; ++newline)
      newLineTb->item[newline] = oldLineTb->item[newline];

  /* Now copy function lines one by one. */

  for (ii = 0; ii < function_count; ++ii)
    {
      for (jj = fentry[ii].line + 1;
	   jj < oldLineTb->nitems && oldLineTb->item[jj].line != 0;
	   ++jj, ++newline)
	newLineTb->item[newline] = oldLineTb->item[jj];
    }
  xfree (fentry);
  newLineTb->nitems = oldLineTb->nitems - function_count;
  return newLineTb;
}