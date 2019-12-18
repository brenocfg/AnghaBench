#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nitems; int nitems_max; char const** item; } ;
typedef  TYPE_1__ string_list_ty ;

/* Variables and functions */
 int /*<<< orphan*/  REALLOC_ARRAY (char const**,int) ; 

__attribute__((used)) static inline void
string_list_append (string_list_ty *slp, const char *s)
{
  /* Grow the list.  */
  if (slp->nitems >= slp->nitems_max)
    {
      slp->nitems_max = slp->nitems_max * 2 + 4;
      REALLOC_ARRAY(slp->item, slp->nitems_max);
    }

  /* Add the string to the end of the list.  */
  slp->item[slp->nitems++] = s;
}