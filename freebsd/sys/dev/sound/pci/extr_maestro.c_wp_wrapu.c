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
typedef  unsigned int u_int16_t ;
struct agg_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPREG_CRAM_PTR ; 
 int /*<<< orphan*/  WPREG_DATA_PORT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wp_wait_data (struct agg_info*,unsigned int) ; 
 int /*<<< orphan*/  wp_wrreg (struct agg_info*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
wp_wrapu(struct agg_info *ess, unsigned ch, u_int16_t reg, u_int16_t data)
{
	wp_wrreg(ess, WPREG_CRAM_PTR, reg | (ch << 4));
	if (wp_wait_data(ess, reg | (ch << 4)) == 0) {
		wp_wrreg(ess, WPREG_DATA_PORT, data);
		if (wp_wait_data(ess, data) != 0)
			device_printf(ess->dev,
			    "wp_wrapu() write timed out.\n");
	} else {
		device_printf(ess->dev, "wp_wrapu() indexing timed out.\n");
	}
}