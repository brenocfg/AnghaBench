#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_9__ {scalar_t__ s_active; int /*<<< orphan*/  sati_device; } ;
struct TYPE_10__ {TYPE_1__ stp_device; } ;
struct TYPE_15__ {TYPE_2__ protocol_device; TYPE_6__* domain; } ;
struct TYPE_14__ {TYPE_5__* controller; } ;
struct TYPE_11__ {int /*<<< orphan*/  ignore_fua; scalar_t__ max_ncq_depth; int /*<<< orphan*/  is_sata_ncq_enabled; } ;
struct TYPE_12__ {TYPE_3__ sas; } ;
struct TYPE_13__ {TYPE_4__ user_parameters; } ;
typedef  TYPE_7__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_device_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scif_sas_stp_remote_device_construct(
   SCIF_SAS_REMOTE_DEVICE_T * device
)
{
   sati_device_construct(
      &device->protocol_device.stp_device.sati_device,
      device->domain->controller->user_parameters.sas.is_sata_ncq_enabled,
      (U8) device->domain->controller->user_parameters.sas.max_ncq_depth,
      device->domain->controller->user_parameters.sas.ignore_fua
   );

   device->protocol_device.stp_device.s_active = 0;
}