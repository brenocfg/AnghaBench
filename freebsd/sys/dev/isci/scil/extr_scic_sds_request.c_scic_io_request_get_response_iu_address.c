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
struct TYPE_2__ {void* response_buffer; } ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */

void * scic_io_request_get_response_iu_address(
   SCI_IO_REQUEST_HANDLE_T scic_io_request
)
{
   SCIC_SDS_REQUEST_T * this_request = (SCIC_SDS_REQUEST_T *)scic_io_request;

   return this_request->response_buffer;
}