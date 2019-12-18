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
typedef  int /*<<< orphan*/  u32 ;
struct sysc {scalar_t__* offsets; int module_size; int /*<<< orphan*/  module_va; int /*<<< orphan*/  module_pa; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 size_t SYSC_REVISION ; 
 size_t SYSC_SYSCONFIG ; 
 size_t SYSC_SYSSTATUS ; 
 int SZ_1K ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max3 (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sysc_ioremap(struct sysc *ddata)
{
	int size;

	if (ddata->offsets[SYSC_REVISION] < 0 &&
	    ddata->offsets[SYSC_SYSCONFIG] < 0 &&
	    ddata->offsets[SYSC_SYSSTATUS] < 0) {
		size = ddata->module_size;
	} else {
		size = max3(ddata->offsets[SYSC_REVISION],
			    ddata->offsets[SYSC_SYSCONFIG],
			    ddata->offsets[SYSC_SYSSTATUS]);

		if (size < SZ_1K)
			size = SZ_1K;

		if ((size + sizeof(u32)) > ddata->module_size)
			size = ddata->module_size;
	}

	ddata->module_va = devm_ioremap(ddata->dev,
					ddata->module_pa,
					size + sizeof(u32));
	if (!ddata->module_va)
		return -EIO;

	return 0;
}