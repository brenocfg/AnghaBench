#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_13__ {scalar_t__ sgl_set; scalar_t__ sgl_offset; TYPE_1__* sgl_pair; } ;
struct TYPE_14__ {scalar_t__ current_transfer_bytes; TYPE_2__ request_current; } ;
struct TYPE_15__ {TYPE_3__ pio; } ;
struct TYPE_17__ {TYPE_4__ type; } ;
struct TYPE_16__ {scalar_t__ length; } ;
struct TYPE_12__ {TYPE_5__ B; TYPE_5__ A; } ;
typedef  TYPE_5__ SCU_SGL_ELEMENT_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_6__ SCIC_SDS_STP_REQUEST_T ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ SCU_SGL_ELEMENT_PAIR_A ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  scic_cb_io_request_copy_buffer (TYPE_6__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ scic_cb_io_request_get_virtual_address_from_sgl (TYPE_6__*,scalar_t__) ; 
 TYPE_5__* scic_sds_stp_request_pio_get_next_sgl (TYPE_6__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_request_pio_data_in_copy_data_buffer(
   SCIC_SDS_STP_REQUEST_T * this_request,
   U8                     * data_buffer,
   U32                      length
)
{
   SCI_STATUS          status;
   SCU_SGL_ELEMENT_T * current_sgl;
   U32                 sgl_offset;
   U32                 data_offset;
   U8                * source_address;

   // Initial setup to get the current working SGL and the offset within the buffer
   current_sgl =
      (this_request->type.pio.request_current.sgl_set == SCU_SGL_ELEMENT_PAIR_A) ?
         &(this_request->type.pio.request_current.sgl_pair->A) :
         &(this_request->type.pio.request_current.sgl_pair->B) ;

   sgl_offset = this_request->type.pio.request_current.sgl_offset;

   source_address = data_buffer;
   data_offset = this_request->type.pio.current_transfer_bytes;
   status = SCI_SUCCESS;

   // While we are still doing Ok and there is more data to transfer
   while (
            (length > 0)
         && (status == SCI_SUCCESS)
         )
   {
      if (current_sgl->length == sgl_offset)
      {
         // This SGL has been exauhasted so we need to get the next SGL
         current_sgl = scic_sds_stp_request_pio_get_next_sgl(this_request);

         if (current_sgl == NULL)
            status = SCI_FAILURE;
         else
            sgl_offset = 0;
      }
      else
      {
#ifdef ENABLE_OSSL_COPY_BUFFER
         scic_cb_io_request_copy_buffer(this_request, data_buffer, data_offset, length);
         length = 0;
#else
         U8 * destination_address;
         U32  copy_length;

         destination_address = (U8 *)scic_cb_io_request_get_virtual_address_from_sgl(
            this_request,
            data_offset
         );

         copy_length = MIN(length, current_sgl->length - sgl_offset);

         memcpy(destination_address, source_address, copy_length);

         length -= copy_length;
         sgl_offset += copy_length;
         data_offset += copy_length;
         source_address += copy_length;
#endif
      }
   }

   this_request->type.pio.request_current.sgl_offset = sgl_offset;

   return status;
}