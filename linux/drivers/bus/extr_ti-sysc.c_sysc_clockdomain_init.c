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
struct ti_sysc_platform_data {int (* init_clockdomain ) (int /*<<< orphan*/ ,struct clk*,struct clk*,int /*<<< orphan*/ *) ;} ;
struct sysc {int nr_clocks; int /*<<< orphan*/  cookie; int /*<<< orphan*/  dev; struct clk** clocks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t SYSC_FCK ; 
 size_t SYSC_ICK ; 
 struct ti_sysc_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct clk*,struct clk*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sysc_clockdomain_init(struct sysc *ddata)
{
	struct ti_sysc_platform_data *pdata = dev_get_platdata(ddata->dev);
	struct clk *fck = NULL, *ick = NULL;
	int error;

	if (!pdata || !pdata->init_clockdomain)
		return 0;

	switch (ddata->nr_clocks) {
	case 2:
		ick = ddata->clocks[SYSC_ICK];
		/* fallthrough */
	case 1:
		fck = ddata->clocks[SYSC_FCK];
		break;
	case 0:
		return 0;
	}

	error = pdata->init_clockdomain(ddata->dev, fck, ick, &ddata->cookie);
	if (!error || error == -ENODEV)
		return 0;

	return error;
}