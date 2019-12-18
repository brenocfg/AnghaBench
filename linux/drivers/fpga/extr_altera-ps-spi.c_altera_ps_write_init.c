#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_ps_conf* priv; } ;
struct fpga_image_info {int flags; } ;
struct altera_ps_conf {int info_flags; TYPE_1__* data; int /*<<< orphan*/  status; int /*<<< orphan*/  config; } ;
struct TYPE_2__ {int status_wait_min_us; int status_wait_max_us; int /*<<< orphan*/  t_st2ck_us; int /*<<< orphan*/  t_cfg_us; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  altera_ps_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int altera_ps_write_init(struct fpga_manager *mgr,
				struct fpga_image_info *info,
				const char *buf, size_t count)
{
	struct altera_ps_conf *conf = mgr->priv;
	int min, max, waits;
	int i;

	conf->info_flags = info->flags;

	if (info->flags & FPGA_MGR_PARTIAL_RECONFIG) {
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		return -EINVAL;
	}

	gpiod_set_value_cansleep(conf->config, 1);

	/* wait min reset pulse time */
	altera_ps_delay(conf->data->t_cfg_us);

	if (!gpiod_get_value_cansleep(conf->status)) {
		dev_err(&mgr->dev, "Status pin failed to show a reset\n");
		return -EIO;
	}

	gpiod_set_value_cansleep(conf->config, 0);

	min = conf->data->status_wait_min_us;
	max = conf->data->status_wait_max_us;
	waits = max / min;
	if (max % min)
		waits++;

	/* wait for max { max(t_STATUS), max(t_CF2ST1) } */
	for (i = 0; i < waits; i++) {
		usleep_range(min, min + 10);
		if (!gpiod_get_value_cansleep(conf->status)) {
			/* wait for min(t_ST2CK)*/
			altera_ps_delay(conf->data->t_st2ck_us);
			return 0;
		}
	}

	dev_err(&mgr->dev, "Status pin not ready.\n");
	return -EIO;
}