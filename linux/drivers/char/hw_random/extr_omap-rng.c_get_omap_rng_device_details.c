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
struct omap_rng_dev {int /*<<< orphan*/ * pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap2_rng_pdata ; 

__attribute__((used)) static int get_omap_rng_device_details(struct omap_rng_dev *omap_rng)
{
	/* Only OMAP2/3 can be non-DT */
	omap_rng->pdata = &omap2_rng_pdata;
	return 0;
}