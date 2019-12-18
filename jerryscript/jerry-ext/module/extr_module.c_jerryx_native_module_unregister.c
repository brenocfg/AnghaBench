#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next_p; } ;
typedef  TYPE_1__ jerryx_native_module_t ;

/* Variables and functions */
 TYPE_1__* first_module_p ; 

void jerryx_native_module_unregister (jerryx_native_module_t *module_p)
{
  jerryx_native_module_t *parent_p = NULL, *iter_p = NULL;

  for (iter_p = first_module_p; iter_p != NULL; parent_p = iter_p, iter_p = iter_p->next_p)
  {
    if (iter_p == module_p)
    {
      if (parent_p)
      {
        parent_p->next_p = module_p->next_p;
      }
      else
      {
        first_module_p = module_p->next_p;
      }
      module_p->next_p = NULL;
    }
  }
}