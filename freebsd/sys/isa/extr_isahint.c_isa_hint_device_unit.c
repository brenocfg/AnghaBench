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
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_match_resource_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ resource_find_dev (int*,char const*,int*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ resource_long_value (char const*,int,char*,long*) ; 
 int /*<<< orphan*/  resource_string_value (char const*,int,char*,char const**) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
isa_hint_device_unit(device_t bus, device_t child, const char *name, int *unitp)
{
	const char *s;
	long value;
	int line, matches, unit;

	line = 0;
	for (;;) {
		if (resource_find_dev(&line, name, &unit, "at", NULL) != 0)
			break;

		/* Must have an "at" for isa. */
		resource_string_value(name, unit, "at", &s);
		if (!(strcmp(s, device_get_nameunit(bus)) == 0 ||
		    strcmp(s, device_get_name(bus)) == 0))
			continue;

		/*
		 * Check for matching resources.  We must have at
		 * least one match.  Since I/O and memory resources
		 * cannot be shared, if we get a match on either of
		 * those, ignore any mismatches in IRQs or DRQs.
		 *
		 * XXX: We may want to revisit this to be more lenient
		 * and wire as long as it gets one match.
		 */
		matches = 0;
		if (resource_long_value(name, unit, "port", &value) == 0) {
			/*
			 * Floppy drive controllers are notorious for
			 * having a wide variety of resources not all
			 * of which include the first port that is
			 * specified by the hint (typically 0x3f0)
			 * (see the comment above
			 * fdc_isa_alloc_resources() in fdc_isa.c).
			 * However, they do all seem to include port +
			 * 2 (e.g. 0x3f2) so for a floppy device, look
			 * for 'value + 2' in the port resources
			 * instead of the hint value.
			 */
			if (strcmp(name, "fdc") == 0)
				value += 2;
			if (isa_match_resource_hint(child, SYS_RES_IOPORT,
			    value))
				matches++;
			else
				continue;
		}
		if (resource_long_value(name, unit, "maddr", &value) == 0) {
			if (isa_match_resource_hint(child, SYS_RES_MEMORY,
			    value))
				matches++;
			else
				continue;
		}
		if (matches > 0)
			goto matched;
		if (resource_long_value(name, unit, "irq", &value) == 0) {
			if (isa_match_resource_hint(child, SYS_RES_IRQ, value))
				matches++;
			else
				continue;
		}
		if (resource_long_value(name, unit, "drq", &value) == 0) {
			if (isa_match_resource_hint(child, SYS_RES_DRQ, value))
				matches++;
			else
				continue;
		}

	matched:
		if (matches > 0) {
			/* We have a winner! */
			*unitp = unit;
			break;
		}
	}
}