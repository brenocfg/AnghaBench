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
struct TYPE_2__ {scalar_t__ next_index; scalar_t__ length; scalar_t__ next_mdl; } ;
typedef  scalar_t__ SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T ;
typedef  TYPE_1__ SCI_BASE_MEMORY_DESCRIPTOR_LIST_T ;

/* Variables and functions */
 scalar_t__ SCI_INVALID_HANDLE ; 

void sci_mdl_next_entry(
   SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T mdl
)
{
   SCI_BASE_MEMORY_DESCRIPTOR_LIST_T * base_mdl = (SCI_BASE_MEMORY_DESCRIPTOR_LIST_T*) mdl;

   // If there is at least one more entry left in the array, then change
   // the next pointer to it.
   if (base_mdl->next_index < base_mdl->length)
      base_mdl->next_index++;
   else if (base_mdl->next_index == base_mdl->length)
   {
      // This MDL has exhausted it's set of entries.  If this MDL is managing
      // another MDL, then start iterating through that MDL.
      if (base_mdl->next_mdl != SCI_INVALID_HANDLE)
         sci_mdl_next_entry(base_mdl->next_mdl);
   }
}