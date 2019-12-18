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
struct TYPE_7__ {int phy_index; } ;
struct TYPE_6__ {int enabled_phy_mask; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sds_phy_resume (TYPE_2__*) ; 

__attribute__((used)) static
void scic_sds_port_resume_phy(
   SCIC_SDS_PORT_T * this_port,
   SCIC_SDS_PHY_T  * the_phy
)
{
   scic_sds_phy_resume (the_phy);
   this_port->enabled_phy_mask |= 1 << the_phy->phy_index;
}