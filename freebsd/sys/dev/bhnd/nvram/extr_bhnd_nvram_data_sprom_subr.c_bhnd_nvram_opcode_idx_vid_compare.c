#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t vid; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */

__attribute__((used)) static int
bhnd_nvram_opcode_idx_vid_compare(const void *key, const void *rhs)
{
	const bhnd_sprom_opcode_idx_entry	*entry;
	size_t				 	 vid;

	vid = *(const size_t *)key;
	entry = rhs;

	if (vid < entry->vid)
		return (-1);
	if (vid > entry->vid)
		return (1);

	return (0);
}