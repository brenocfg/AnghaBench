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
struct ivhd_dev_cfg {scalar_t__ enable_ats; int /*<<< orphan*/  data; int /*<<< orphan*/  end_id; int /*<<< orphan*/  start_id; } ;
struct amdvi_softc {int dev_cfg_cnt; int /*<<< orphan*/  dev; struct ivhd_dev_cfg* dev_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
amdvi_print_dev_cap(struct amdvi_softc *softc)
{
	struct ivhd_dev_cfg *cfg;
	int i;

	cfg = softc->dev_cfg;
	for (i = 0; i < softc->dev_cfg_cnt; i++) {
		device_printf(softc->dev, "device [0x%x - 0x%x]"
		    "config:%b%s\n", cfg->start_id, cfg->end_id,
		    cfg->data,
		    "\020\001INIT\002ExtInt\003NMI"
		    "\007LINT0\008LINT1",
		    cfg->enable_ats ? "ATS enabled" : "");
		cfg++;
	}
}