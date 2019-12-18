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
struct sysc {int /*<<< orphan*/  dev; scalar_t__* clocks; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 size_t SYSC_FCK ; 
 size_t SYSC_ICK ; 
 int SYSC_MAX_CLOCKS ; 
 int SYSC_OPTFCK0 ; 
 int clk_prepare (scalar_t__) ; 
 int /*<<< orphan*/ * clock_names ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int sysc_get_one_clock(struct sysc *ddata, const char *name)
{
	int error, i, index = -ENODEV;

	if (!strncmp(clock_names[SYSC_FCK], name, 3))
		index = SYSC_FCK;
	else if (!strncmp(clock_names[SYSC_ICK], name, 3))
		index = SYSC_ICK;

	if (index < 0) {
		for (i = SYSC_OPTFCK0; i < SYSC_MAX_CLOCKS; i++) {
			if (!ddata->clocks[i]) {
				index = i;
				break;
			}
		}
	}

	if (index < 0) {
		dev_err(ddata->dev, "clock %s not added\n", name);
		return index;
	}

	ddata->clocks[index] = devm_clk_get(ddata->dev, name);
	if (IS_ERR(ddata->clocks[index])) {
		dev_err(ddata->dev, "clock get error for %s: %li\n",
			name, PTR_ERR(ddata->clocks[index]));

		return PTR_ERR(ddata->clocks[index]);
	}

	error = clk_prepare(ddata->clocks[index]);
	if (error) {
		dev_err(ddata->dev, "clock prepare error for %s: %i\n",
			name, error);

		return error;
	}

	return 0;
}