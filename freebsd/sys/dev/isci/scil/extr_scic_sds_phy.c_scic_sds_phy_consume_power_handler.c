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
struct TYPE_7__ {TYPE_1__* state_handlers; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* consume_power_handler ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_2__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

SCI_STATUS scic_sds_phy_consume_power_handler(
   SCIC_SDS_PHY_T *this_phy
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_sds_phy_consume_power_handler(this_phy:0x%08x)\n",
      this_phy
   ));

   return this_phy->state_handlers->consume_power_handler(this_phy);
}