#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  void SCIF_SAS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ sci_object_get_association (void*) ; 
 int /*<<< orphan*/ * scif_cb_io_request_get_virtual_address_from_sgl (scalar_t__,int /*<<< orphan*/ ) ; 

U8 *scic_cb_io_request_get_virtual_address_from_sgl(
   void * scic_user_io_request,
   U32    byte_offset
)
{
   SCIF_SAS_REQUEST_T *fw_request =
      (SCIF_SAS_REQUEST_T *) sci_object_get_association(scic_user_io_request);

   return scif_cb_io_request_get_virtual_address_from_sgl(
             sci_object_get_association(fw_request),
             byte_offset
          );
}