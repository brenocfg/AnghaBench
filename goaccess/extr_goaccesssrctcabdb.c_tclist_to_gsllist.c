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
typedef  int /*<<< orphan*/  TCLIST ;
typedef  int /*<<< orphan*/  GSLList ;

/* Variables and functions */
 int /*<<< orphan*/  int2ptr (int) ; 
 int /*<<< orphan*/ * list_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_insert_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tclistnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tclistval (int /*<<< orphan*/ *,int,int*) ; 

GSLList *
tclist_to_gsllist (TCLIST * tclist)
{
  GSLList *list = NULL;
  int i, sz;
  int *val;

  for (i = 0; i < tclistnum (tclist); ++i) {
    val = (int *) tclistval (tclist, i, &sz);
    if (list == NULL)
      list = list_create (int2ptr (*val));
    else
      list = list_insert_prepend (list, int2ptr (*val));
  }

  return list;
}