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
struct tegra_dfll {size_t mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_DISABLED ; 
 size_t DFLL_OPEN_LOOP ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_set_mode (struct tegra_dfll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mode_name ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dfll_disable(struct tegra_dfll *td)
{
	if (td->mode != DFLL_OPEN_LOOP) {
		dev_err(td->dev, "cannot disable DFLL in %s mode\n",
			mode_name[td->mode]);
		return -EINVAL;
	}

	dfll_set_mode(td, DFLL_DISABLED);
	pm_runtime_put_sync(td->dev);

	return 0;
}