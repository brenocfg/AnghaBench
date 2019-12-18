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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_get_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ofw_pcibus_parse_associativity (int /*<<< orphan*/ ,int*) ; 

int
ofw_pcibus_get_domain(device_t dev, device_t child, int *domain)
{
	int d, error;

	error = ofw_pcibus_parse_associativity(child, &d);
	/* No ofw node; go up a level */
	if (error)
		return (bus_generic_get_domain(dev, child, domain));
	*domain = d;
	return (0);
}