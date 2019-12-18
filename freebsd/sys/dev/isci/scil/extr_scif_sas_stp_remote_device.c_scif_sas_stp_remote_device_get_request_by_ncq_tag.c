#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ protocol; } ;
struct TYPE_6__ {scalar_t__ ncq_tag; TYPE_1__ sequence; } ;
struct SCIF_SAS_REQUEST {TYPE_2__ stp; struct SCIF_SAS_REMOTE_DEVICE* device; } ;
struct SCIF_SAS_REMOTE_DEVICE {TYPE_4__* domain; } ;
typedef  scalar_t__ U8 ;
struct TYPE_7__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_8__ {TYPE_3__ request_list; } ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  struct SCIF_SAS_REQUEST SCIF_SAS_REQUEST_T ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 scalar_t__ SAT_PROTOCOL_FPDMA ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 

struct SCIF_SAS_REQUEST *
scif_sas_stp_remote_device_get_request_by_ncq_tag(
   struct SCIF_SAS_REMOTE_DEVICE * fw_device,
   U8                              ncq_tag
)
{
   SCIF_SAS_DOMAIN_T                * fw_domain = fw_device->domain;
   SCI_FAST_LIST_ELEMENT_T          * pending_request_element;
   SCIF_SAS_REQUEST_T               * pending_request = NULL;
   SCIF_SAS_REQUEST_T               * matching_request = NULL;

   pending_request_element = fw_domain->request_list.list_head;

   while (pending_request_element != NULL)
   {
      pending_request =
         (SCIF_SAS_REQUEST_T*) sci_fast_list_get_object(pending_request_element);

      // The current element may be deleted from the list because of
      // IO completion so advance to the next element early
      pending_request_element = sci_fast_list_get_next(pending_request_element);

      if (
            (pending_request->device == fw_device) &&
            (pending_request->stp.sequence.protocol == SAT_PROTOCOL_FPDMA) &&
            (pending_request->stp.ncq_tag == ncq_tag)
         )
      {
         matching_request = pending_request;
      }
   }

   return matching_request;
}