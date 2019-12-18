#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_9__ {int /*<<< orphan*/ * smp_activity_timer; int /*<<< orphan*/  io_retry_count; } ;
struct TYPE_8__ {TYPE_3__ smp_device; } ;
struct TYPE_10__ {TYPE_2__ protocol_device; TYPE_1__* domain; } ;
struct TYPE_7__ {scalar_t__ controller; } ;
typedef  int /*<<< orphan*/  SCI_TIMER_CALLBACK_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/ * scif_cb_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  scif_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scif_sas_smp_internal_request_retry ; 

void scif_sas_smp_remote_device_retry_internal_io(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   U8                         io_retry_count,
   U32                        delay
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_retry_internal_io(0x%x, 0x%x, 0x%x) enter\n",
      fw_device, io_retry_count, delay
   ));

   fw_device->protocol_device.smp_device.io_retry_count =
      io_retry_count;

   //create the timer for poll target device's coming back.
   if (fw_device->protocol_device.smp_device.smp_activity_timer == NULL)
   {
      fw_device->protocol_device.smp_device.smp_activity_timer =
         scif_cb_timer_create(
            (SCI_CONTROLLER_HANDLE_T *)fw_device->domain->controller,
            (SCI_TIMER_CALLBACK_T)scif_sas_smp_internal_request_retry,
            (void*)fw_device
         );
   }
   else
   {
      ASSERT(0);
   }
   //start the timer for a purpose of waiting.
   scif_cb_timer_start(
      (SCI_CONTROLLER_HANDLE_T)fw_device->domain->controller,
      fw_device->protocol_device.smp_device.smp_activity_timer,
      delay
   );
}