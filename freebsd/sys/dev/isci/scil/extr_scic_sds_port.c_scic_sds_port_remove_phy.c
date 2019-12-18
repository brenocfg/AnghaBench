#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; TYPE_2__* state_handlers; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* remove_phy_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_3__ SCIC_SDS_PORT_T ;
typedef  TYPE_4__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_port_remove_phy(
   SCIC_SDS_PORT_T * this_port,
   SCIC_SDS_PHY_T  * the_phy
)
{
   return this_port->state_handlers->parent.remove_phy_handler(
                                          &this_port->parent, &the_phy->parent);
}