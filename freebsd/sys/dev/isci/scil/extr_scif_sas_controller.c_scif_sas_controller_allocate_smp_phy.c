#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  smp_phy_memory_list; } ;
typedef  int /*<<< orphan*/  SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_fast_list_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_remove_head (int /*<<< orphan*/ *) ; 

SCIF_SAS_SMP_PHY_T * scif_sas_controller_allocate_smp_phy(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   SCIF_SAS_SMP_PHY_T * smp_phy;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER,
      "scif_controller_allocate_smp_phy(0x%x) enter\n",
      fw_controller
   ));

   if( !sci_fast_list_is_empty(&fw_controller->smp_phy_memory_list) )
   {
      smp_phy = (SCIF_SAS_SMP_PHY_T *)
         sci_fast_list_remove_head(&fw_controller->smp_phy_memory_list);

      //clean the memory.
      memset((char*)smp_phy,
             0,
             sizeof(SCIF_SAS_SMP_PHY_T)
            );

      return smp_phy;
   }
   else
      return NULL;
}