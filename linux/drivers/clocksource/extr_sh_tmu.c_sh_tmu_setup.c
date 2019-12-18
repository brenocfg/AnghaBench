#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_tmu_device {unsigned int num_channels; int rate; int /*<<< orphan*/  clk; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * channels; struct platform_device* pdev; int /*<<< orphan*/  model; int /*<<< orphan*/  lock; } ;
struct sh_timer_config {int /*<<< orphan*/  channels_mask; } ;
struct platform_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_3__ {struct sh_timer_config* platform_data; scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; struct platform_device_id* id_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (TYPE_1__*,char*) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 unsigned int hweight8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_tmu_device*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int sh_tmu_channel_setup (int /*<<< orphan*/ *,unsigned int,int,int,struct sh_tmu_device*) ; 
 int sh_tmu_map_memory (struct sh_tmu_device*) ; 
 int sh_tmu_parse_dt (struct sh_tmu_device*) ; 

__attribute__((used)) static int sh_tmu_setup(struct sh_tmu_device *tmu, struct platform_device *pdev)
{
	unsigned int i;
	int ret;

	tmu->pdev = pdev;

	raw_spin_lock_init(&tmu->lock);

	if (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) {
		ret = sh_tmu_parse_dt(tmu);
		if (ret < 0)
			return ret;
	} else if (pdev->dev.platform_data) {
		const struct platform_device_id *id = pdev->id_entry;
		struct sh_timer_config *cfg = pdev->dev.platform_data;

		tmu->model = id->driver_data;
		tmu->num_channels = hweight8(cfg->channels_mask);
	} else {
		dev_err(&tmu->pdev->dev, "missing platform data\n");
		return -ENXIO;
	}

	/* Get hold of clock. */
	tmu->clk = clk_get(&tmu->pdev->dev, "fck");
	if (IS_ERR(tmu->clk)) {
		dev_err(&tmu->pdev->dev, "cannot get clock\n");
		return PTR_ERR(tmu->clk);
	}

	ret = clk_prepare(tmu->clk);
	if (ret < 0)
		goto err_clk_put;

	/* Determine clock rate. */
	ret = clk_enable(tmu->clk);
	if (ret < 0)
		goto err_clk_unprepare;

	tmu->rate = clk_get_rate(tmu->clk) / 4;
	clk_disable(tmu->clk);

	/* Map the memory resource. */
	ret = sh_tmu_map_memory(tmu);
	if (ret < 0) {
		dev_err(&tmu->pdev->dev, "failed to remap I/O memory\n");
		goto err_clk_unprepare;
	}

	/* Allocate and setup the channels. */
	tmu->channels = kcalloc(tmu->num_channels, sizeof(*tmu->channels),
				GFP_KERNEL);
	if (tmu->channels == NULL) {
		ret = -ENOMEM;
		goto err_unmap;
	}

	/*
	 * Use the first channel as a clock event device and the second channel
	 * as a clock source.
	 */
	for (i = 0; i < tmu->num_channels; ++i) {
		ret = sh_tmu_channel_setup(&tmu->channels[i], i,
					   i == 0, i == 1, tmu);
		if (ret < 0)
			goto err_unmap;
	}

	platform_set_drvdata(pdev, tmu);

	return 0;

err_unmap:
	kfree(tmu->channels);
	iounmap(tmu->mapbase);
err_clk_unprepare:
	clk_unprepare(tmu->clk);
err_clk_put:
	clk_put(tmu->clk);
	return ret;
}