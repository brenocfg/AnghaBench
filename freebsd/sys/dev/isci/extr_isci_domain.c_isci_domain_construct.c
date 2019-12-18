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
struct ISCI_DOMAIN {int /*<<< orphan*/  sci_object; struct ISCI_CONTROLLER* controller; int /*<<< orphan*/  index; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  scif_controller_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  scif_controller_get_domain_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isci_domain_construct(struct ISCI_DOMAIN *domain, uint32_t domain_index,
    struct ISCI_CONTROLLER *controller)
{

	scif_controller_get_domain_handle( controller->scif_controller_handle,
	    domain_index, &domain->sci_object);

	domain->index = domain_index;
	domain->controller = controller;
	sci_object_set_association(domain->sci_object, (void *)domain);
}