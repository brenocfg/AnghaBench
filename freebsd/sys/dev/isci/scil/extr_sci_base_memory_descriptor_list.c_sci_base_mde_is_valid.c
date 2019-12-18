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
typedef  int U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_3__ {int constant_memory_alignment; int constant_memory_size; scalar_t__ constant_memory_attributes; int /*<<< orphan*/ * virtual_address; int /*<<< orphan*/  physical_address; } ;
typedef  TYPE_1__ SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int sci_cb_physical_address_lower (int /*<<< orphan*/ ) ; 

BOOL sci_base_mde_is_valid(
   SCI_PHYSICAL_MEMORY_DESCRIPTOR_T * mde,
   U32                                alignment,
   U32                                size,
   U16                                attributes
)
{
   // Only need the lower 32 bits to ensure alignment is met.
   U32 physical_address = sci_cb_physical_address_lower(mde->physical_address);

   if (
         ((physical_address & (alignment - 1)) != 0)
      || (mde->constant_memory_alignment != alignment)
      || (mde->constant_memory_size != size)
      || (mde->virtual_address == NULL)
      || (mde->constant_memory_attributes != attributes)
      )
   {
      return FALSE;
   }

   return TRUE;
}