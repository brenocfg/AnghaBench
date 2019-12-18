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
struct omap_sr {int /*<<< orphan*/  voltdm; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_vp_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_disable (struct omap_sr*) ; 
 int /*<<< orphan*/  sr_disable_errgen (struct omap_sr*) ; 
 int /*<<< orphan*/  voltdm_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sr_class3_disable(struct omap_sr *sr, int is_volt_reset)
{
	sr_disable_errgen(sr);
	omap_vp_disable(sr->voltdm);
	sr_disable(sr);
	if (is_volt_reset)
		voltdm_reset(sr->voltdm);

	return 0;
}