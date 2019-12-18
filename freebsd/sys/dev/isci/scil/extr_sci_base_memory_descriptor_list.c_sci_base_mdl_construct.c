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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {int /*<<< orphan*/  next_mdl; scalar_t__ next_index; int /*<<< orphan*/ * mde_array; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  int /*<<< orphan*/  SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T ;
typedef  TYPE_1__ SCI_BASE_MEMORY_DESCRIPTOR_LIST_T ;

/* Variables and functions */

void sci_base_mdl_construct(
   SCI_BASE_MEMORY_DESCRIPTOR_LIST_T * mdl,
   SCI_PHYSICAL_MEMORY_DESCRIPTOR_T  * mde_array,
   U32                                 mde_array_length,
   SCI_MEMORY_DESCRIPTOR_LIST_HANDLE_T next_mdl
)
{
   mdl->length     = mde_array_length;
   mdl->mde_array  = mde_array;
   mdl->next_index = 0;
   mdl->next_mdl   = next_mdl;
}