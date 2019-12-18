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
struct densities {int dens; char const* name; } ;

/* Variables and functions */
 struct densities* dens ; 

const char *
mt_density_name(int density_num)
{
	struct densities *sd;

	/* densities 0 and 0x7f are handled as special cases */
	if (density_num == 0)
		return ("default");
	if (density_num == 0x7f)
		return ("same");

	for (sd = dens; sd->dens != 0; sd++)
		if (sd->dens == density_num)
			break;
	if (sd->dens == 0)
		return ("UNKNOWN");
	return (sd->name);
}