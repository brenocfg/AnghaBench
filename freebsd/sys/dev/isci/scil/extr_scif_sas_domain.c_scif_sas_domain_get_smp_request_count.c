#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
struct TYPE_5__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_7__ {TYPE_1__ request_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  core_object; } ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  TYPE_2__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_DOMAIN_T ;
typedef  scalar_t__ SCIC_TRANSPORT_PROTOCOL ;

/* Variables and functions */
 scalar_t__ SCIC_SMP_PROTOCOL ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_io_request_get_protocol (int /*<<< orphan*/ ) ; 

U8 scif_sas_domain_get_smp_request_count(
   SCIF_SAS_DOMAIN_T * fw_domain
)
{
   SCI_FAST_LIST_ELEMENT_T * element = fw_domain->request_list.list_head;
   SCIF_SAS_REQUEST_T      * request = NULL;
   U8                        count = 0;
   SCIC_TRANSPORT_PROTOCOL   protocol;

   // Cycle through the fast list of IO requests.  Terminate each
   // outstanding requests that matches the criteria supplied by the
   // caller.
   while (element != NULL)
   {
      request = (SCIF_SAS_REQUEST_T*) sci_fast_list_get_object(element);
      // The current element may be deleted from the list because of
      // IO completion so advance to the next element early
      element = sci_fast_list_get_next(element);

      protocol = scic_io_request_get_protocol(request->core_object);

      if ( protocol == SCIC_SMP_PROTOCOL)
         count++;
   }

   return count;
}