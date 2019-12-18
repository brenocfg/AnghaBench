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
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct ivhd_dev_cfg {int enable_ats; scalar_t__ data; void* end_id; void* start_id; } ;
struct amdvi_softc {int /*<<< orphan*/  dev_cfg_cnt; struct ivhd_dev_cfg* dev_cfg; } ;

/* Variables and functions */

__attribute__((used)) static void
ivhd_dev_add_entry(struct amdvi_softc *softc, uint32_t start_id,
    uint32_t end_id, uint8_t cfg, bool ats)
{
	struct ivhd_dev_cfg *dev_cfg;

	/* If device doesn't have special data, don't add it. */
	if (!cfg)
		return;

	dev_cfg = &softc->dev_cfg[softc->dev_cfg_cnt++];
	dev_cfg->start_id = start_id;
	dev_cfg->end_id = end_id;
	dev_cfg->data = cfg;
	dev_cfg->enable_ats = ats;
}