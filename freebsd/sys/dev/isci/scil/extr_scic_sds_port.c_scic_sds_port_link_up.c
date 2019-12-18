#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  is_in_link_training; } ;
struct TYPE_9__ {TYPE_1__* state_handlers; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* link_up_handler ) (TYPE_2__*,TYPE_3__*) ;} ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;
typedef  TYPE_3__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__*) ; 

void scic_sds_port_link_up(
   SCIC_SDS_PORT_T *this_port,
   SCIC_SDS_PHY_T  *the_phy
)
{
   the_phy->is_in_link_training = FALSE;

   this_port->state_handlers->link_up_handler(this_port, the_phy);
}