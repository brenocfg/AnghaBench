#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_8__ {TYPE_1__ device_address; } ;
struct TYPE_7__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_2__ SCI_SAS_ADDRESS_T ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_3__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 

void scic_remote_device_get_sas_address(
   SCI_REMOTE_DEVICE_HANDLE_T   remote_device,
   SCI_SAS_ADDRESS_T          * sas_address
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device;
   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)remote_device;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_get_sas_address(0x%x, 0x%x) enter\n",
      remote_device, sas_address
   ));

   sas_address->low = this_device->device_address.low;
   sas_address->high = this_device->device_address.high;
}