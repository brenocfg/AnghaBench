#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {scalar_t__ attached_stp_target; } ;
struct TYPE_7__ {TYPE_1__ bits; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ target_protocols; } ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_4__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_RESET_TIMEOUT ; 
 int /*<<< orphan*/  SCIC_SDS_SIGNATURE_FIS_TIMEOUT ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 

U32 scic_remote_device_get_suggested_reset_timeout(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device;
   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)remote_device;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_get_suggested_reset_timeout(0x%x) enter\n",
      remote_device
   ));

   if (this_device->target_protocols.u.bits.attached_stp_target)
   {
      return SCIC_SDS_SIGNATURE_FIS_TIMEOUT;
   }

   return SCIC_SDS_REMOTE_DEVICE_RESET_TIMEOUT;
}