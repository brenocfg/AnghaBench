#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scic_sds_port_general_link_up_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_reset_state_link_up_handler(
   SCIC_SDS_PORT_T *this_port,
   SCIC_SDS_PHY_T  *phy
)
{
   /// @todo We should make sure that the phy that has gone link up is the same
   ///       one on which we sent the reset.  It is possible that the phy on
   ///       which we sent the reset is not the one that has gone link up and we
   ///       want to make sure that phy being reset comes back.  Consider the
   ///       case where a reset is sent but before the hardware processes the
   ///       reset it get a link up on the port because of a hot plug event.
   ///       because of the reset request this phy will go link down almost
   ///       immediately.

   // In the resetting state we don't notify the user regarding
   // link up and link down notifications.
   scic_sds_port_general_link_up_handler(this_port, phy, FALSE, TRUE);
}