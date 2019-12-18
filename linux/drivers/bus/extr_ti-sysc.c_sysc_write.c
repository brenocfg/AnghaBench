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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int quirks; } ;
struct sysc {int* offsets; scalar_t__ module_va; TYPE_1__ cfg; } ;

/* Variables and functions */
 int SYSC_QUIRK_16BIT ; 
 size_t SYSC_REVISION ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  writew_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sysc_write(struct sysc *ddata, int offset, u32 value)
{
	if (ddata->cfg.quirks & SYSC_QUIRK_16BIT) {
		writew_relaxed(value & 0xffff, ddata->module_va + offset);

		/* Only i2c revision has LO and HI register with stride of 4 */
		if (ddata->offsets[SYSC_REVISION] >= 0 &&
		    offset == ddata->offsets[SYSC_REVISION]) {
			u16 hi = value >> 16;

			writew_relaxed(hi, ddata->module_va + offset + 4);
		}

		return;
	}

	writel_relaxed(value, ddata->module_va + offset);
}