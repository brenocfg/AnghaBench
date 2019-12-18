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
struct sysc {int /*<<< orphan*/  rsts; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_optional_shared (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sysc_init_resets(struct sysc *ddata)
{
	ddata->rsts =
		devm_reset_control_get_optional_shared(ddata->dev, "rstctrl");
	if (IS_ERR(ddata->rsts))
		return PTR_ERR(ddata->rsts);

	return 0;
}