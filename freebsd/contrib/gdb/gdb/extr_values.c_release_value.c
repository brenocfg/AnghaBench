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
struct value {struct value* next; } ;

/* Variables and functions */
 struct value* all_values ; 

void
release_value (struct value *val)
{
  struct value *v;

  if (all_values == val)
    {
      all_values = val->next;
      return;
    }

  for (v = all_values; v; v = v->next)
    {
      if (v->next == val)
	{
	  v->next = val->next;
	  break;
	}
    }
}