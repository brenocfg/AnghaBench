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
typedef  int /*<<< orphan*/  uint32_t ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  scif_controller_handle; } ;
typedef  int /*<<< orphan*/ * SCI_PHY_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_controller_get_phy_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  scic_phy_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_controller_get_scic_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isci_sysctl_start(struct ISCI_CONTROLLER *controller,
    uint32_t phy_to_be_started)
{
	SCI_PHY_HANDLE_T phy_handle = NULL;

	scic_controller_get_phy_handle(
	    scif_controller_get_scic_handle(controller->scif_controller_handle),
	    phy_to_be_started, &phy_handle);

	scic_phy_start(phy_handle);
}