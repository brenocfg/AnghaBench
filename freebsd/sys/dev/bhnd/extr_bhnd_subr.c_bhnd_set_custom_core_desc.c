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
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 char* bhnd_get_vendor_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 

void
bhnd_set_custom_core_desc(device_t dev, const char *dev_name)
{
	const char *vendor_name;
	char *desc;

	vendor_name = bhnd_get_vendor_name(dev);
	asprintf(&desc, M_BHND, "%s %s, rev %hhu", vendor_name, dev_name,
	    bhnd_get_hwrev(dev));

	if (desc != NULL) {
		device_set_desc_copy(dev, desc);
		free(desc, M_BHND);
	} else {
		device_set_desc(dev, dev_name);
	}
}