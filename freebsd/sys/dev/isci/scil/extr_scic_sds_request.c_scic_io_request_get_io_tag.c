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
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_2__ {int /*<<< orphan*/  io_tag; } ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 

U16 scic_io_request_get_io_tag(
   SCI_IO_REQUEST_HANDLE_T  scic_io_request
)
{
   SCIC_SDS_REQUEST_T *this_request;
   this_request = (SCIC_SDS_REQUEST_T *)scic_io_request;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(scic_io_request),
      SCIC_LOG_OBJECT_SMP_IO_REQUEST,
      "scic_io_request_get_io_tag(0x%x) enter\n",
      scic_io_request
   ));

   return this_request->io_tag;
}