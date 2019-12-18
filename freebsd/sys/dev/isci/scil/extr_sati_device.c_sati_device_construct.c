#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_3__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  ncq_depth; int /*<<< orphan*/  descriptor_sense_enable; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SATI_DEVICE_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_DEVICE_CAP_IGNORE_FUA ; 
 int /*<<< orphan*/  SATI_DEVICE_CAP_NCQ_REQUESTED_ENABLE ; 
 int /*<<< orphan*/  SATI_DEVICE_STATE_OPERATIONAL ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_CONTROL_D_SENSE_DISABLE ; 
 scalar_t__ TRUE ; 

void sati_device_construct(
   SATI_DEVICE_T * device,
   BOOL            is_ncq_enabled,
   U8              max_ncq_depth,
   BOOL            ignore_fua
)
{
   device->state                   = SATI_DEVICE_STATE_OPERATIONAL;
   device->capabilities            = 0;
   device->descriptor_sense_enable = SCSI_MODE_PAGE_CONTROL_D_SENSE_DISABLE;

   // The user requested that NCQ be utilized if it is supported by
   // the device.
   if (is_ncq_enabled == TRUE)
      device->capabilities |= SATI_DEVICE_CAP_NCQ_REQUESTED_ENABLE;

   device->ncq_depth      = max_ncq_depth;

   // The user requested that FUA is ignored (windows performance issue)
   if (ignore_fua == TRUE)
      device->capabilities |= SATI_DEVICE_CAP_IGNORE_FUA;

}