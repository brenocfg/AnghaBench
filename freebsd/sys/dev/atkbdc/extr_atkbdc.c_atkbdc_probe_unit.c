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
struct resource {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ rman_get_start (struct resource*) ; 

int
atkbdc_probe_unit(int unit, struct resource *port0, struct resource *port1)
{
	if (rman_get_start(port0) <= 0)
		return ENXIO;
	if (rman_get_start(port1) <= 0)
		return ENXIO;
	return 0;
}