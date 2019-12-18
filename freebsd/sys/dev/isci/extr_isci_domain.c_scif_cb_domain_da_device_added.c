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
typedef  int /*<<< orphan*/  uint8_t ;
struct ISCI_REMOTE_DEVICE {struct ISCI_DOMAIN* domain; int /*<<< orphan*/  sci_object; } ;
struct ISCI_DOMAIN {struct ISCI_REMOTE_DEVICE* da_remote_device; } ;
typedef  int /*<<< orphan*/  SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCI_SAS_ADDRESS_T ;
typedef  int /*<<< orphan*/  SCI_DOMAIN_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ ,struct ISCI_REMOTE_DEVICE*) ; 
 int /*<<< orphan*/  scif_remote_device_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_remote_device_da_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
scif_cb_domain_da_device_added(SCI_CONTROLLER_HANDLE_T controller,
    SCI_DOMAIN_HANDLE_T domain, SCI_SAS_ADDRESS_T *sas_address,
    SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T *protocols)
{
	struct ISCI_REMOTE_DEVICE *remote_device;
	struct ISCI_DOMAIN *isci_domain =
	    (struct ISCI_DOMAIN *)sci_object_get_association(domain);

	/*
	 * For direct-attached devices, do not pull the device object from
	 *  the pool.  Rather, use the one stored in the domain object which
	 *  will ensure that we always get consistent target ids for direct
	 *  attached devices.
	 */
	remote_device = isci_domain->da_remote_device;

	scif_remote_device_construct(domain,
	    (uint8_t*)remote_device + sizeof(struct ISCI_REMOTE_DEVICE),
	    &(remote_device->sci_object));

	sci_object_set_association(remote_device->sci_object, remote_device);

	scif_remote_device_da_construct(remote_device->sci_object, sas_address,
	    protocols);

	/* We do not put the device in the ISCI_CONTROLLER's device array yet.
	 *  That will happen once the device becomes ready (see
	 *  scif_cb_remote_device_ready).
	 */

	remote_device->domain = isci_domain;
}