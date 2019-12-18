#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U16 ;
struct TYPE_8__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_11__ {TYPE_1__ request_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_10__ {TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  TYPE_2__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_IO_REQUEST_T ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_io_request_get_io_tag (int /*<<< orphan*/ ) ; 

SCIF_SAS_REQUEST_T * scif_sas_domain_get_request_by_io_tag(
   SCIF_SAS_DOMAIN_T * fw_domain,
   U16                 io_tag
)
{
   SCI_FAST_LIST_ELEMENT_T * element    = fw_domain->request_list.list_head;
   SCIF_SAS_IO_REQUEST_T   * io_request = NULL;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_domain_get_request_by_io_tag(0x%x, 0x%x) enter\n",
      fw_domain, io_tag
   ));

   while (element != NULL)
   {
      io_request = (SCIF_SAS_IO_REQUEST_T*) sci_fast_list_get_object(element);

      // Check to see if we located the request with an identical IO tag.
      if (scic_io_request_get_io_tag(io_request->parent.core_object) == io_tag)
         return &io_request->parent;

      element = sci_fast_list_get_next(element);
   }

   return NULL;
}