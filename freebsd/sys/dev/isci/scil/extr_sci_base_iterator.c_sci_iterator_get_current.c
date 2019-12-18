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
struct TYPE_2__ {int /*<<< orphan*/ * current; } ;
typedef  scalar_t__ SCI_ITERATOR_HANDLE_T ;
typedef  TYPE_1__ SCI_BASE_ITERATOR_T ;

/* Variables and functions */
 void* sci_abstract_list_get_object (int /*<<< orphan*/ *) ; 

void * sci_iterator_get_current(
   SCI_ITERATOR_HANDLE_T iterator_handle
)
{
   SCI_BASE_ITERATOR_T * iterator = (SCI_BASE_ITERATOR_T *)iterator_handle;

   void *current_object = NULL;

   if (iterator->current != NULL)
   {
      current_object = sci_abstract_list_get_object(iterator->current);
   }

   return current_object;
}