#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  remote_device_list; } ;
struct TYPE_13__ {int /*<<< orphan*/  scheduled_activity; } ;
struct TYPE_10__ {TYPE_4__ smp_device; } ;
struct TYPE_15__ {TYPE_1__ protocol_device; int /*<<< orphan*/  core_object; } ;
struct TYPE_11__ {scalar_t__ attached_smp_target; } ;
struct TYPE_12__ {TYPE_2__ bits; } ;
struct TYPE_14__ {TYPE_3__ u; } ;
typedef  TYPE_5__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCI_ABSTRACT_ELEMENT_T ;
typedef  TYPE_6__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_7__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION ; 
 int /*<<< orphan*/ * sci_abstract_list_get_front (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sci_abstract_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_abstract_list_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_5__*) ; 

void scif_sas_domain_schedule_clear_affiliation(
   SCIF_SAS_DOMAIN_T * fw_domain
)
{
   SCI_ABSTRACT_ELEMENT_T * current_element =
      sci_abstract_list_get_front(&fw_domain->remote_device_list);

   SCIF_SAS_REMOTE_DEVICE_T * current_device;
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T  dev_protocols;

   //config route table activity has higher priority than discover activity.
   while ( current_element != NULL )
   {
      current_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                       sci_abstract_list_get_object(current_element);

      scic_remote_device_get_protocols(current_device->core_object,
                                       &dev_protocols);

      current_element =
         sci_abstract_list_get_next(current_element);

      if ( dev_protocols.u.bits.attached_smp_target )
      {
         current_device->protocol_device.smp_device.scheduled_activity =
            SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION;
      }
   }
}