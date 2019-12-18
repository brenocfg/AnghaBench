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
struct densities {int dens; int bpi; int bpmm; } ;

/* Variables and functions */
 struct densities* dens ; 

int
mt_density_bp(int density_num, int bpi)
{
	struct densities *sd;

	for (sd = dens; sd->dens; sd++)
		if (sd->dens == density_num)
			break;
	if (sd->dens == 0)
		return (0);
	if (bpi)
		return (sd->bpi);
	else
		return (sd->bpmm);
}