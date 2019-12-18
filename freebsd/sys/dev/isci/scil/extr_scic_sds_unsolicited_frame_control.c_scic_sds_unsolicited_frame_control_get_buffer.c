#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_8__ {TYPE_2__* array; } ;
struct TYPE_6__ {size_t count; } ;
struct TYPE_9__ {TYPE_3__ buffers; TYPE_1__ address_table; } ;
struct TYPE_7__ {void* buffer; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_4__ SCIC_SDS_UNSOLICITED_FRAME_CONTROL_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 

SCI_STATUS scic_sds_unsolicited_frame_control_get_buffer(
   SCIC_SDS_UNSOLICITED_FRAME_CONTROL_T *uf_control,
   U32                                   frame_index,
   void                                **frame_buffer
)
{
   if (frame_index < uf_control->address_table.count)
   {
      *frame_buffer = uf_control->buffers.array[frame_index].buffer;

      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INVALID_PARAMETER_VALUE;
}