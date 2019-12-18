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
struct TYPE_5__ {int /*<<< orphan*/  associated_object; } ;
struct TYPE_6__ {TYPE_1__ parent; } ;
struct TYPE_7__ {TYPE_2__ parent; } ;
struct TYPE_8__ {TYPE_3__ parent; } ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_ADDRESS ;
typedef  TYPE_4__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_cb_sge_get_address_field (int /*<<< orphan*/ ,void*) ; 

SCI_PHYSICAL_ADDRESS scic_cb_sge_get_address_field(
   void * scic_user_io_request,
   void * sge_address
)
{
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T*)
                                   scic_user_io_request;
   return scif_cb_sge_get_address_field(
             fw_io->parent.parent.parent.associated_object, sge_address
          );
}