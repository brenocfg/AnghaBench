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
struct varobj_root {struct varobj_root* next; struct varobj* rootvar; } ;
struct varobj {int dummy; } ;

/* Variables and functions */
 int rootcount ; 
 struct varobj_root* rootlist ; 
 int /*<<< orphan*/  warning (char*,int,int) ; 
 struct varobj** xmalloc (int) ; 

int
varobj_list (struct varobj ***varlist)
{
  struct varobj **cv;
  struct varobj_root *croot;
  int mycount = rootcount;

  /* Alloc (rootcount + 1) entries for the result */
  *varlist = xmalloc ((rootcount + 1) * sizeof (struct varobj *));

  cv = *varlist;
  croot = rootlist;
  while ((croot != NULL) && (mycount > 0))
    {
      *cv = croot->rootvar;
      mycount--;
      cv++;
      croot = croot->next;
    }
  /* Mark the end of the list */
  *cv = NULL;

  if (mycount || (croot != NULL))
    warning
      ("varobj_list: assertion failed - wrong tally of root vars (%d:%d)",
       rootcount, mycount);

  return rootcount;
}