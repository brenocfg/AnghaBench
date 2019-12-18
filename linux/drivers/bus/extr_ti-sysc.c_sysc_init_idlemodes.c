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
struct TYPE_2__ {int /*<<< orphan*/  sidlemodes; int /*<<< orphan*/  midlemodes; } ;
struct sysc {TYPE_1__ cfg; } ;

/* Variables and functions */
 int sysc_init_idlemode (struct sysc*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int sysc_init_idlemodes(struct sysc *ddata)
{
	int error;

	error = sysc_init_idlemode(ddata, &ddata->cfg.midlemodes,
				   "ti,sysc-midle");
	if (error)
		return error;

	error = sysc_init_idlemode(ddata, &ddata->cfg.sidlemodes,
				   "ti,sysc-sidle");
	if (error)
		return error;

	return 0;
}