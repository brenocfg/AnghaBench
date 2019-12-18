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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pccard_get_product (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pccard_get_product_str (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ pccard_get_vendor (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pccard_get_vendor_str (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
pccard_set_default_descr(device_t dev)
{
	const char *vendorstr, *prodstr;
	uint32_t vendor, prod;
	char *str;

	if (pccard_get_vendor_str(dev, &vendorstr))
		return (0);
	if (pccard_get_product_str(dev, &prodstr))
		return (0);
	if (vendorstr != NULL && prodstr != NULL) {
		str = malloc(strlen(vendorstr) + strlen(prodstr) + 2, M_DEVBUF,
		    M_WAITOK);
		sprintf(str, "%s %s", vendorstr, prodstr);
		device_set_desc_copy(dev, str);
		free(str, M_DEVBUF);
	} else {
		if (pccard_get_vendor(dev, &vendor))
			return (0);
		if (pccard_get_product(dev, &prod))
			return (0);
		str = malloc(100, M_DEVBUF, M_WAITOK);
		snprintf(str, 100, "vendor=%#x product=%#x", vendor, prod);
		device_set_desc_copy(dev, str);
		free(str, M_DEVBUF);
	}
	return (0);
}