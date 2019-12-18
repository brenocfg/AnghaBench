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
struct sysc {int /*<<< orphan*/  module_size; int /*<<< orphan*/  module_pa; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SYSC_MAX_REGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sysc_show_name (char*,struct sysc*) ; 
 int /*<<< orphan*/  sysc_show_reg (struct sysc*,char*,int) ; 
 int /*<<< orphan*/  sysc_show_rev (char*,struct sysc*) ; 

__attribute__((used)) static void sysc_show_registers(struct sysc *ddata)
{
	char buf[128];
	char *bufp = buf;
	int i;

	for (i = 0; i < SYSC_MAX_REGS; i++)
		bufp += sysc_show_reg(ddata, bufp, i);

	bufp += sysc_show_rev(bufp, ddata);
	bufp += sysc_show_name(bufp, ddata);

	dev_dbg(ddata->dev, "%llx:%x%s\n",
		ddata->module_pa, ddata->module_size,
		buf);
}