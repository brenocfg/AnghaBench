#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ current_activity; } ;
struct TYPE_7__ {TYPE_1__ smp_device; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; TYPE_3__* state_handlers; TYPE_2__ protocol_device; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  list_element; int /*<<< orphan*/  core_object; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* complete_high_priority_io_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_IO_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_DOMAIN_T ;
typedef  TYPE_4__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  scalar_t__ SCIC_TRANSPORT_PROTOCOL ;

/* Variables and functions */
 scalar_t__ SCIC_SMP_PROTOCOL ; 
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_fast_list_remove_element (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_io_request_get_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_domain_ready_complete_high_priority_io_handler(
   SCI_BASE_DOMAIN_T        * domain,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request,
   void                     * response_data,
   SCI_IO_STATUS              completion_status
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   SCIF_SAS_REQUEST_T       * fw_request= (SCIF_SAS_REQUEST_T*) io_request;

   SCIC_TRANSPORT_PROTOCOL    protocol;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_domain_ready_complete_high_priority_io_handler(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      domain, remote_device, io_request, response_data
   ));

   protocol = scic_io_request_get_protocol(fw_request->core_object);

   // If the request is an SMP HARD/LINK RESET request, then the request
   // came through the task management path (partially).  As a result,
   // the accounting for the request is managed in the task request
   // completion path.  Thus, only change the domain request counter if
   // the request is not an SMP target reset of some sort.
   if (
         (protocol != SCIC_SMP_PROTOCOL)
      || (fw_device->protocol_device.smp_device.current_activity !=
                SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET)
      )
   {
      sci_fast_list_remove_element(&fw_request->list_element);
   }

   return fw_device->state_handlers->complete_high_priority_io_handler(
             &fw_device->parent, &fw_request->parent, response_data, completion_status
          );
}