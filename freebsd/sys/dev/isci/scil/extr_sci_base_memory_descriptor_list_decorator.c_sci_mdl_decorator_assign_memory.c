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
typedef  int U64 ;
typedef  scalar_t__ U32 ;
struct TYPE_3__ {scalar_t__ constant_memory_attributes; int constant_memory_alignment; scalar_t__ constant_memory_size; int /*<<< orphan*/  physical_address; void* virtual_address; } ;
typedef  TYPE_1__ SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_ADDRESS ;
typedef  int /*<<< orphan*/  SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T ;
typedef  int POINTER_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  sci_cb_make_physical_address (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ sci_cb_physical_address_lower (int /*<<< orphan*/ ) ; 
 scalar_t__ sci_cb_physical_address_upper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_mdl_first_entry (int /*<<< orphan*/ ) ; 
 TYPE_1__* sci_mdl_get_current_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_mdl_next_entry (int /*<<< orphan*/ ) ; 

void sci_mdl_decorator_assign_memory(
   SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T mdl,
   U32                                 attributes,
   POINTER_UINT                        virtual_address,
   SCI_PHYSICAL_ADDRESS                sci_physical_address
)
{
   SCI_PHYSICAL_MEMORY_DESCRIPTOR_T * mde;
   U64  physical_address;

   physical_address
      =   ((U64) sci_cb_physical_address_lower(sci_physical_address))
        | (((U64) sci_cb_physical_address_upper(sci_physical_address)) << 32);

   sci_mdl_first_entry(mdl);
   mde = sci_mdl_get_current_entry(mdl);
   while (mde != NULL)
   {
      // As long as the memory attribute for this MDE is equivalent to
      // those supplied by the caller, then fill out the appropriate
      // MDE fields.
      if (  (mde->constant_memory_attributes == attributes)
         || (attributes == 0) )
      {
         // Ensure the virtual address alignment rules are met.
         if ((virtual_address % mde->constant_memory_alignment) != 0)
         {
            virtual_address
               += (mde->constant_memory_alignment -
                   (virtual_address % mde->constant_memory_alignment));
         }

         // Ensure the physical address alignment rules are met.
         if ((physical_address % mde->constant_memory_alignment) != 0)
         {
            physical_address
               += (mde->constant_memory_alignment -
                   (physical_address % mde->constant_memory_alignment));
         }

         // Update the MDE with properly aligned address values.
         mde->virtual_address  = (void *)virtual_address;
         sci_cb_make_physical_address(
            mde->physical_address,
            (U32) (physical_address >> 32),
            (U32) (physical_address & 0xFFFFFFFF)
         );

         virtual_address  += mde->constant_memory_size;
         physical_address += mde->constant_memory_size;
      }

      // Move on to the next MDE
      sci_mdl_next_entry(mdl);
      mde = sci_mdl_get_current_entry (mdl);
   }
}