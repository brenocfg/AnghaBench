#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pbar; int /*<<< orphan*/  pulser; scalar_t__ indeterminate; } ;
typedef  TYPE_1__ uiProgressBar ;
typedef  int gdouble ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  g_source_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_fraction (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pulse ; 
 int /*<<< orphan*/  uiprivUserBug (char*,int) ; 

void uiProgressBarSetValue(uiProgressBar *p, int value)
{
	if (value == -1) {
		if (!p->indeterminate) {
			p->indeterminate = TRUE;
			// TODO verify the timeout
			p->pulser = g_timeout_add(100, pulse, p);
		}
		return;
	}
	if (p->indeterminate) {
		p->indeterminate = FALSE;
		g_source_remove(p->pulser);
	}

	if (value < 0 || value > 100)
		uiprivUserBug("Value %d is out of range for a uiProgressBar.", value);

	gtk_progress_bar_set_fraction(p->pbar, ((gdouble) value) / 100);
}