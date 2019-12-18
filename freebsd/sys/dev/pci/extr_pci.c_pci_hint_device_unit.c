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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  me2 ;
typedef  int /*<<< orphan*/  me1 ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_domain (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_find_dev (int*,char const*,int*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_string_value (char const*,int,char*,char const**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
pci_hint_device_unit(device_t dev, device_t child, const char *name, int *unitp)
{
	int line, unit;
	const char *at;
	char me1[24], me2[32];
	uint8_t b, s, f;
	uint32_t d;

	d = pci_get_domain(child);
	b = pci_get_bus(child);
	s = pci_get_slot(child);
	f = pci_get_function(child);
	snprintf(me1, sizeof(me1), "pci%u:%u:%u", b, s, f);
	snprintf(me2, sizeof(me2), "pci%u:%u:%u:%u", d, b, s, f);
	line = 0;
	while (resource_find_dev(&line, name, &unit, "at", NULL) == 0) {
		resource_string_value(name, unit, "at", &at);
		if (strcmp(at, me1) != 0 && strcmp(at, me2) != 0)
			continue; /* No match, try next candidate */
		*unitp = unit;
		return;
	}
}