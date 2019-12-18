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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/  scu_status; } ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */

U32 scic_request_get_controller_status(
   SCI_IO_REQUEST_HANDLE_T  io_request
)
{
   SCIC_SDS_REQUEST_T * this_request = (SCIC_SDS_REQUEST_T*)io_request;
   return this_request->scu_status;
}