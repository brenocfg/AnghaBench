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
struct TYPE_2__ {int quirks; } ;
struct sysc {TYPE_1__ cfg; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int SYSC_QUIRK_16BIT ; 
 int SYSC_QUIRK_USE_CLOCKACT ; 
 int resource_size (struct resource*) ; 

__attribute__((used)) static void sysc_check_quirk_16bit(struct sysc *ddata, struct resource *res)
{
	if (resource_size(res) == 8)
		ddata->cfg.quirks |= SYSC_QUIRK_16BIT | SYSC_QUIRK_USE_CLOCKACT;
}