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
struct TYPE_6__ {int quirks; int syss_mask; } ;
struct sysc {int* offsets; int /*<<< orphan*/  (* reset_done_quirk ) (struct sysc*) ;TYPE_3__ cfg; int /*<<< orphan*/  (* clk_enable_quirk ) (struct sysc*) ;int /*<<< orphan*/  (* clk_disable_quirk ) (struct sysc*) ;TYPE_2__* cap; scalar_t__ legacy_mode; } ;
struct TYPE_5__ {TYPE_1__* regbits; } ;
struct TYPE_4__ {scalar_t__ srst_shift; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  MAX_MODULE_SOFTRESET_WAIT ; 
 int SYSC_QUIRK_NO_RESET_ON_INIT ; 
 int SYSC_QUIRK_RESET_STATUS ; 
 size_t SYSC_SYSCONFIG ; 
 size_t SYSC_SYSSTATUS ; 
 int SYSS_QUIRK_RESETDONE_INVERTED ; 
 int readx_poll_timeout (int (*) (struct sysc*),struct sysc*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sysc*) ; 
 int /*<<< orphan*/  stub2 (struct sysc*) ; 
 int /*<<< orphan*/  stub3 (struct sysc*) ; 
 int sysc_read_sysconfig (struct sysc*) ; 
 int sysc_read_sysstatus (struct sysc*) ; 
 int /*<<< orphan*/  sysc_write (struct sysc*,int,int) ; 

__attribute__((used)) static int sysc_reset(struct sysc *ddata)
{
	int sysc_offset, syss_offset, sysc_val, rstval, error = 0;
	u32 sysc_mask, syss_done;

	sysc_offset = ddata->offsets[SYSC_SYSCONFIG];
	syss_offset = ddata->offsets[SYSC_SYSSTATUS];

	if (ddata->legacy_mode || sysc_offset < 0 ||
	    ddata->cap->regbits->srst_shift < 0 ||
	    ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT)
		return 0;

	sysc_mask = BIT(ddata->cap->regbits->srst_shift);

	if (ddata->cfg.quirks & SYSS_QUIRK_RESETDONE_INVERTED)
		syss_done = 0;
	else
		syss_done = ddata->cfg.syss_mask;

	if (ddata->clk_disable_quirk)
		ddata->clk_disable_quirk(ddata);

	sysc_val = sysc_read_sysconfig(ddata);
	sysc_val |= sysc_mask;
	sysc_write(ddata, sysc_offset, sysc_val);

	if (ddata->clk_enable_quirk)
		ddata->clk_enable_quirk(ddata);

	/* Poll on reset status */
	if (syss_offset >= 0) {
		error = readx_poll_timeout(sysc_read_sysstatus, ddata, rstval,
					   (rstval & ddata->cfg.syss_mask) ==
					   syss_done,
					   100, MAX_MODULE_SOFTRESET_WAIT);

	} else if (ddata->cfg.quirks & SYSC_QUIRK_RESET_STATUS) {
		error = readx_poll_timeout(sysc_read_sysconfig, ddata, rstval,
					   !(rstval & sysc_mask),
					   100, MAX_MODULE_SOFTRESET_WAIT);
	}

	if (ddata->reset_done_quirk)
		ddata->reset_done_quirk(ddata);

	return error;
}