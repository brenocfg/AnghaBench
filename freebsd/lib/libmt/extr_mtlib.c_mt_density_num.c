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
struct densities {int dens; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct densities* dens ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char const*,size_t) ; 

int
mt_density_num(const char *density_name)
{
	struct densities *sd;
	size_t l = strlen(density_name);

	for (sd = dens; sd->dens; sd++)
		if (strncasecmp(sd->name, density_name, l) == 0)
			break;
	return (sd->dens);
}