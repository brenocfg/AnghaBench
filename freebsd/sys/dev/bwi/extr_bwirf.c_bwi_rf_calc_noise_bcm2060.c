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
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int BWI_NOISE_FLOOR ; 

__attribute__((used)) static int
bwi_rf_calc_noise_bcm2060(struct bwi_mac *mac)
{
	/* XXX Dont know how to calc */
	return (BWI_NOISE_FLOOR);
}