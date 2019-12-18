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
struct ISCI_CONTROLLER {scalar_t__ is_started; } ;
typedef  int /*<<< orphan*/  SCI_DOMAIN_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TIMEOUT ; 
 scalar_t__ TRUE ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_domain_discover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_domain_get_suggested_discover_timeout (int /*<<< orphan*/ ) ; 

void
scif_cb_domain_change_notification(SCI_CONTROLLER_HANDLE_T controller,
    SCI_DOMAIN_HANDLE_T domain)
{
	struct ISCI_CONTROLLER *isci_controller =
	    (struct ISCI_CONTROLLER *)sci_object_get_association(controller);

	/* When the controller start is complete, we will explicitly discover
	 *  all of the domains then.  This is because SCIF will not allow
	 *  any I/O to start until the controller is ready, meaning internal SMP
	 *  requests triggered by domain discovery won't work until the controller
	 *  is ready.
	 */
	if (isci_controller->is_started == TRUE)
	    scif_domain_discover(domain,
	        scif_domain_get_suggested_discover_timeout(domain),
	        DEVICE_TIMEOUT);
}