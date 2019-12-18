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
typedef  scalar_t__ uint8_t ;
struct smbios_structure_header {int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  (* smbios_callback_t ) (struct smbios_structure_header*,void*) ;

/* Variables and functions */

__attribute__((used)) static void
smbios_walk_table(uint8_t *p, int entries, smbios_callback_t cb, void *arg)
{
	struct smbios_structure_header *s;

	while (entries--) {
		s = (struct smbios_structure_header *)p;
		cb(s, arg);

		/*
		 * Look for a double-nul after the end of the
		 * formatted area of this structure.
		 */
		p += s->length;
		while (!(p[0] == 0 && p[1] == 0))
			p++;

		/*
		 * Skip over the double-nul to the start of the next
		 * structure.
		 */
		p += 2;
	}
}