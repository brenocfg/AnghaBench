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
struct TYPE_2__ {size_t next_index; size_t length; scalar_t__ next_mdl; int /*<<< orphan*/ * mde_array; } ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  scalar_t__ SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T ;
typedef  TYPE_1__ SCI_BASE_MEMORY_DESCRIPTOR_LIST_T ;

/* Variables and functions */
 scalar_t__ SCI_INVALID_HANDLE ; 

SCI_PHYSICAL_MEMORY_DESCRIPTOR_T * sci_mdl_get_current_entry(
   SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T mdl
)
{
   SCI_BASE_MEMORY_DESCRIPTOR_LIST_T * base_mdl = (SCI_BASE_MEMORY_DESCRIPTOR_LIST_T*) mdl;

   if (base_mdl->next_index < base_mdl->length)
      return & base_mdl->mde_array[base_mdl->next_index];
   else if (base_mdl->next_index == base_mdl->length)
   {
      // This MDL has exhausted it's set of entries.  If this MDL is managing
      // another MDL, then return it's current entry.
      if (base_mdl->next_mdl != SCI_INVALID_HANDLE)
         return sci_mdl_get_current_entry(base_mdl->next_mdl);
   }

   return NULL;
}