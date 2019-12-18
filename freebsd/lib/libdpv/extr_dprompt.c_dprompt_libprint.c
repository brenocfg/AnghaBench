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

/* Variables and functions */
 scalar_t__ DPV_APROMPT_MAX ; 
 int DPV_DISPLAY_LIMIT ; 
 scalar_t__ DPV_PPROMPT_MAX ; 
 int /*<<< orphan*/  dheight ; 
 int /*<<< orphan*/  dlg_reallocate_gauge (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dlg_update_gauge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprompt_sprint (char*,char const*,char const*) ; 
 int /*<<< orphan*/  dwidth ; 
 int /*<<< orphan*/  gauge ; 
 int gauge_percent ; 
 char* title ; 

void
dprompt_libprint(const char *prefix, const char *append, int overall)
{
	int percent = gauge_percent;
	char buf[DPV_PPROMPT_MAX + DPV_APROMPT_MAX + DPV_DISPLAY_LIMIT * 1024];

	dprompt_sprint(buf, prefix, append);

	if (overall >= 0 && overall <= 100)
		gauge_percent = percent = overall;
	gauge = dlg_reallocate_gauge(gauge, title == NULL ? "" : title,
	    buf, dheight, dwidth, percent);
	dlg_update_gauge(gauge, percent);
}