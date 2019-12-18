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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_EXCL ; 
 int RF_SHAREABLE ; 
 scalar_t__ bus_get_domain (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*),void*,int,void**,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int rman_activate_resource (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_irq_cookie (struct resource*,void*) ; 

__attribute__((used)) static int
nexus_setup_intr(device_t bus, device_t child, struct resource *irq,
		 int flags, driver_filter_t filter, void (*ihand)(void *),
		 void *arg, void **cookiep)
{
	int		error, domain;

	/* somebody tried to setup an irq that failed to allocate! */
	if (irq == NULL)
		panic("nexus_setup_intr: NULL irq resource!");

	*cookiep = NULL;
	if ((rman_get_flags(irq) & RF_SHAREABLE) == 0)
		flags |= INTR_EXCL;

	/*
	 * We depend here on rman_activate_resource() being idempotent.
	 */
	error = rman_activate_resource(irq);
	if (error)
		return (error);
	if (bus_get_domain(child, &domain) != 0)
		domain = 0;

	error = intr_add_handler(device_get_nameunit(child),
	    rman_get_start(irq), filter, ihand, arg, flags, cookiep, domain);
	if (error == 0)
		rman_set_irq_cookie(irq, *cookiep);

	return (error);
}