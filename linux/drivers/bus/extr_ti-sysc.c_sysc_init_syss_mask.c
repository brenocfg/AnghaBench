#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int sysc_val; int syss_mask; int /*<<< orphan*/  quirks; } ;
struct sysc {TYPE_2__ cfg; TYPE_1__* cap; TYPE_3__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int SYSC_OMAP4_SOFTRESET ; 
 int /*<<< orphan*/  SYSC_QUIRK_RESET_STATUS ; 
 scalar_t__ TI_SYSC_OMAP4 ; 
 scalar_t__ TI_SYSC_OMAP4_TIMER ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int sysc_init_syss_mask(struct sysc *ddata)
{
	struct device_node *np = ddata->dev->of_node;
	int error;
	u32 val;

	error = of_property_read_u32(np, "ti,syss-mask", &val);
	if (error) {
		if ((ddata->cap->type == TI_SYSC_OMAP4 ||
		     ddata->cap->type == TI_SYSC_OMAP4_TIMER) &&
		    (ddata->cfg.sysc_val & SYSC_OMAP4_SOFTRESET))
			ddata->cfg.quirks |= SYSC_QUIRK_RESET_STATUS;

		return 0;
	}

	if (!(val & 1) && (ddata->cfg.sysc_val & SYSC_OMAP4_SOFTRESET))
		ddata->cfg.quirks |= SYSC_QUIRK_RESET_STATUS;

	ddata->cfg.syss_mask = val;

	return 0;
}