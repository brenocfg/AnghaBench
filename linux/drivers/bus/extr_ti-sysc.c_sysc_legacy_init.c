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
struct ti_sysc_platform_data {int (* init_module ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct sysc {int /*<<< orphan*/  cookie; int /*<<< orphan*/  mdata; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 struct ti_sysc_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sysc_legacy_init(struct sysc *ddata)
{
	struct ti_sysc_platform_data *pdata = dev_get_platdata(ddata->dev);
	int error;

	if (!pdata || !pdata->init_module)
		return 0;

	error = pdata->init_module(ddata->dev, ddata->mdata, &ddata->cookie);
	if (error == -EEXIST)
		error = 0;

	return error;
}