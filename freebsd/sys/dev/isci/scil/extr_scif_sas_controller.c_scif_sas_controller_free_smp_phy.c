#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  smp_phy_memory_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  list_element; } ;
typedef  TYPE_1__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_2__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_fast_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scif_sas_controller_free_smp_phy(
   SCIF_SAS_CONTROLLER_T * fw_controller,
   SCIF_SAS_SMP_PHY_T    * smp_phy
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER,
      "scif_controller_free_smp_phy(0x%x, 0x%x) enter\n",
      fw_controller, smp_phy
   ));

   //return the memory to the list.
   sci_fast_list_insert_tail(
      &fw_controller->smp_phy_memory_list,
      &smp_phy->list_element
   );
}