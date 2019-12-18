#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int U32 ;
struct TYPE_11__ {int count; void** array; void* physical_address; } ;
struct TYPE_10__ {int /*<<< orphan*/ * array; void* physical_address; } ;
struct TYPE_9__ {int count; } ;
struct TYPE_13__ {scalar_t__ get; TYPE_3__ address_table; TYPE_2__ headers; TYPE_1__ buffers; } ;
struct TYPE_12__ {scalar_t__ virtual_address; void* physical_address; } ;
typedef  int /*<<< orphan*/  SCU_UNSOLICITED_FRAME_HEADER_T ;
typedef  TYPE_4__ SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  void* SCI_PHYSICAL_ADDRESS ;
typedef  TYPE_5__ SCIC_SDS_UNSOLICITED_FRAME_CONTROL_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  POINTER_UINT ;

/* Variables and functions */
 int SCU_UNSOLICITED_FRAME_BUFFER_SIZE ; 
 int /*<<< orphan*/  sci_physical_address_add (void*,int) ; 
 int /*<<< orphan*/  sci_physical_address_subtract (void*,int) ; 
 int /*<<< orphan*/  scic_sds_unsolicited_frame_control_construct_frames (TYPE_5__*,void*,int /*<<< orphan*/ ,int,int) ; 

void scic_sds_unsolicited_frame_control_construct(
   SCIC_SDS_UNSOLICITED_FRAME_CONTROL_T *uf_control,
   SCI_PHYSICAL_MEMORY_DESCRIPTOR_T     *mde,
   SCIC_SDS_CONTROLLER_T                *controller
)
{
   U32  unused_uf_header_entries;
   U32  used_uf_header_entries;
   U32  used_uf_buffer_bytes;
   U32  unused_uf_header_bytes;
   U32  used_uf_header_bytes;
   SCI_PHYSICAL_ADDRESS  uf_buffer_phys_address;

   // Prepare all of the memory sizes for the UF headers, UF address
   // table, and UF buffers themselves.
   used_uf_buffer_bytes     = uf_control->buffers.count
                              * SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
   unused_uf_header_entries = uf_control->address_table.count
                              - uf_control->buffers.count;
   used_uf_header_entries   = uf_control->buffers.count;
   unused_uf_header_bytes   = unused_uf_header_entries
                              * sizeof(SCU_UNSOLICITED_FRAME_HEADER_T);
   used_uf_header_bytes     = used_uf_header_entries
                              * sizeof(SCU_UNSOLICITED_FRAME_HEADER_T);

   // The Unsolicited Frame buffers are set at the start of the UF
   // memory descriptor entry.  The headers and address table will be
   // placed after the buffers.
   uf_buffer_phys_address = mde->physical_address;

   // Program the location of the UF header table into the SCU.
   // Notes:
   // - The address must align on a 64-byte boundary. Guaranteed to be
   //   on 64-byte boundary already 1KB boundary for unsolicited frames.
   // - Program unused header entries to overlap with the last
   //   unsolicited frame.  The silicon will never DMA to these unused
   //   headers, since we program the UF address table pointers to
   //   NULL.
   uf_control->headers.physical_address = uf_buffer_phys_address;
   sci_physical_address_add(
      uf_control->headers.physical_address, used_uf_buffer_bytes);
   sci_physical_address_subtract(
      uf_control->headers.physical_address, unused_uf_header_bytes);

   uf_control->headers.array = (SCU_UNSOLICITED_FRAME_HEADER_T*)
      ((U8 *)mde->virtual_address + used_uf_buffer_bytes - unused_uf_header_bytes);

   // Program the location of the UF address table into the SCU.
   // Notes:
   // - The address must align on a 64-bit boundary. Guaranteed to be on 64
   //   byte boundary already due to above programming headers being on a
   //   64-bit boundary and headers are on a 64-bytes in size.
   uf_control->address_table.physical_address = uf_buffer_phys_address;
   sci_physical_address_add(
      uf_control->address_table.physical_address, used_uf_buffer_bytes);
   sci_physical_address_add(
      uf_control->address_table.physical_address, used_uf_header_bytes);

   uf_control->address_table.array = (SCI_PHYSICAL_ADDRESS*)
      ((U8 *)mde->virtual_address + used_uf_buffer_bytes + used_uf_header_bytes);

   uf_control->get = 0;

   // UF buffer requirements are:
   // - The last entry in the UF queue is not NULL.
   // - There is a power of 2 number of entries (NULL or not-NULL)
   //   programmed into the queue.
   // - Aligned on a 1KB boundary.

   // If the user provided less then the maximum amount of memory,
   // then be sure that we programm the first entries in the UF
   // address table to NULL.
   scic_sds_unsolicited_frame_control_construct_frames(
      uf_control,
      uf_buffer_phys_address,
      (POINTER_UINT) mde->virtual_address,
      unused_uf_header_entries,
      used_uf_header_entries
   );
}