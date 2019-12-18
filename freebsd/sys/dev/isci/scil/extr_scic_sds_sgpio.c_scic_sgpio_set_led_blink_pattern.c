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
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  scalar_t__ SCI_PORT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sds_port_get_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sgpio_apply_led_blink_pattern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scic_sgpio_set_led_blink_pattern(
   SCI_CONTROLLER_HANDLE_T controller,
   SCI_PORT_HANDLE_T port_handle,
   BOOL error,
   BOOL locate,
   BOOL activity,
   U8 pattern_selection
)
{
   U32 phy_mask;

   SCIC_SDS_PORT_T * port = (SCIC_SDS_PORT_T *) port_handle;

   phy_mask = scic_sds_port_get_phys(port);

   scic_sgpio_apply_led_blink_pattern(
           controller, phy_mask, error, locate, activity, pattern_selection);
}