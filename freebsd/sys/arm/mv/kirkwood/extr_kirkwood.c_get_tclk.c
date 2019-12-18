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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ MV_DEV_88F6281 ; 
 scalar_t__ MV_DEV_88F6282 ; 
 scalar_t__ TCLK_166MHZ ; 
 scalar_t__ TCLK_200MHZ ; 
 int /*<<< orphan*/  soc_id (scalar_t__*,scalar_t__*) ; 

uint32_t
get_tclk(void)
{
	uint32_t dev, rev;

	/*
	 * On Kirkwood TCLK is not configurable and depends on silicon
	 * revision:
	 * - A0 and A1 have TCLK hardcoded to 200 MHz.
	 * - Z0 and others have TCLK hardcoded to 166 MHz.
	 */
	soc_id(&dev, &rev);
	if (dev == MV_DEV_88F6281 && (rev == 2 || rev == 3))
		return (TCLK_200MHZ);
	if (dev == MV_DEV_88F6282)
		return (TCLK_200MHZ);

	return (TCLK_166MHZ);
}