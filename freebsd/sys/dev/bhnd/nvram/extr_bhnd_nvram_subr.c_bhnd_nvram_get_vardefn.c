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
struct bhnd_nvram_vardefn {int dummy; } ;

/* Variables and functions */
 size_t bhnd_nvram_num_vardefns ; 
 struct bhnd_nvram_vardefn const* bhnd_nvram_vardefns ; 

const struct bhnd_nvram_vardefn *
bhnd_nvram_get_vardefn(size_t id)
{
	if (id >= bhnd_nvram_num_vardefns)
		return (NULL);

	return (&bhnd_nvram_vardefns[id]);
}