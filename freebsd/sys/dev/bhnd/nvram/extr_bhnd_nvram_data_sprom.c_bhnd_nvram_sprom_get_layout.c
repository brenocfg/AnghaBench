#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ rev; } ;
typedef  TYPE_1__ bhnd_sprom_layout ;

/* Variables and functions */
 TYPE_1__ const* bhnd_sprom_layouts ; 
 size_t bhnd_sprom_num_layouts ; 

__attribute__((used)) static const bhnd_sprom_layout *
bhnd_nvram_sprom_get_layout(uint8_t sromrev)
{
	/* Find matching SPROM layout definition */
	for (size_t i = 0; i < bhnd_sprom_num_layouts; i++) {
		if (bhnd_sprom_layouts[i].rev == sromrev)
			return (&bhnd_sprom_layouts[i]);
	}

	/* Not found */
	return (NULL);
}