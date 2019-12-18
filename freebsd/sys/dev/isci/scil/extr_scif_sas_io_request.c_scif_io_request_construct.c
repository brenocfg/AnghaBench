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
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scif_sas_io_request_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_io_request_construct(
   SCI_CONTROLLER_HANDLE_T      scif_controller,
   SCI_REMOTE_DEVICE_HANDLE_T   scif_remote_device,
   U16                          io_tag,
   void                       * user_io_request_object,
   void                       * io_request_memory,
   SCI_IO_REQUEST_HANDLE_T    * scif_io_request
)
{
   SCIF_SAS_IO_REQUEST_T    * fw_io     = (SCIF_SAS_IO_REQUEST_T*)
                                          io_request_memory;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          scif_remote_device;

   return scif_sas_io_request_construct(
             fw_device,
             fw_io,
             io_tag,
             user_io_request_object,
             scif_io_request,
             TRUE
          );
}