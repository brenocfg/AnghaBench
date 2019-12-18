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
struct ofw_compat_data {int /*<<< orphan*/ * ocd_str; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 struct ofw_compat_data* mpc85xx_jog_devcompat () ; 

__attribute__((used)) static int
mpc85xx_jog_probe(device_t dev)
{
	struct ofw_compat_data *compat;

	compat = mpc85xx_jog_devcompat();
	if (compat == NULL || compat->ocd_str == NULL)
		return (ENXIO);

	device_set_desc(dev, "Freescale CPU Jogger");
	return (0);
}