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
 int ENXIO ; 
 int pccard_get_product_str (int /*<<< orphan*/ ,char const**) ; 
 int pccard_get_vendor_str (int /*<<< orphan*/ ,char const**) ; 
 int puc_bfe_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puc_pccard_rscom ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
puc_pccard_probe(device_t dev)
{
	const char *vendor, *product;
	int error;

	error = pccard_get_vendor_str(dev, &vendor);
	if (error)
		return(error);
	error = pccard_get_product_str(dev, &product);
	if (error)
		return(error);
	if (!strcmp(vendor, "PCMCIA") && !strcmp(product, "RS-COM 2P"))
		return (puc_bfe_probe(dev, &puc_pccard_rscom));

	return (ENXIO);
}