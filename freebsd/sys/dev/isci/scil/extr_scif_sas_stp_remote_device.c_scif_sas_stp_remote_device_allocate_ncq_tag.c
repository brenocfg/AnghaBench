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
typedef  scalar_t__ U8 ;
typedef  int U32 ;
struct TYPE_7__ {scalar_t__ ncq_depth; } ;
struct TYPE_8__ {int s_active; TYPE_1__ sati_device; } ;
struct TYPE_9__ {TYPE_2__ stp_device; } ;
struct TYPE_10__ {TYPE_3__ protocol_device; } ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIF_SAS_INVALID_NCQ_TAG ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 

U8 scif_sas_stp_remote_device_allocate_ncq_tag(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   U8  ncq_tag  = 0;
   U32 tag_mask = 1;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_stp_remote_device_allocate_ncq_tag(0x%x)\n",
      fw_device
   ));

   // Try to find an unused NCQ tag.
   while (  (fw_device->protocol_device.stp_device.s_active & tag_mask)
         && (ncq_tag < fw_device->protocol_device.stp_device.sati_device.ncq_depth) )
   {
      tag_mask <<= 1;
      ncq_tag++;
   }

   // Check to see if we were able to find an available NCQ tag.
   if (ncq_tag < fw_device->protocol_device.stp_device.sati_device.ncq_depth)
   {
      SCIF_LOG_INFO((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_IO_REQUEST,
         "RemoteDevice:0x%x NcqTag:0x%x successful NCQ TAG allocation\n",
         fw_device, ncq_tag
      ));

      fw_device->protocol_device.stp_device.s_active |= tag_mask;
      return ncq_tag;
   }

   SCIF_LOG_INFO((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_IO_REQUEST,
      "RemoteDevice:0x%x unable to allocate NCQ TAG\n",
      fw_device
   ));

   // All NCQ tags are in use.
   return SCIF_SAS_INVALID_NCQ_TAG;
}