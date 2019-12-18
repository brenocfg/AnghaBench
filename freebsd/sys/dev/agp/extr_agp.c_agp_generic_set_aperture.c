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
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 

int
agp_generic_set_aperture(device_t dev, u_int32_t aperture)
{
	u_int32_t current_aperture;

	current_aperture = AGP_GET_APERTURE(dev);
	if (current_aperture != aperture)
		return EINVAL;
	else
		return 0;
}