#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ core_object; } ;
typedef  scalar_t__ SCI_LIBRARY_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_LIBRARY_T ;

/* Variables and functions */

SCI_LIBRARY_HANDLE_T scif_library_get_scic_handle(
   SCI_LIBRARY_HANDLE_T   scif_library
)
{
   SCIF_SAS_LIBRARY_T * fw_library = (SCIF_SAS_LIBRARY_T*) scif_library;

   return fw_library->core_object;
}