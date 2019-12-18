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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ drm_do_probe_ddc_edid (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 

bool
drm_probe_ddc(device_t adapter)
{
	unsigned char out;

	return (drm_do_probe_ddc_edid(adapter, &out, 0, 1) == 0);
}