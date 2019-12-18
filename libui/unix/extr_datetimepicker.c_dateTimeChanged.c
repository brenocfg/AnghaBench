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
typedef  int /*<<< orphan*/  uiprivDateTimePickerWidget ;

/* Variables and functions */
 int /*<<< orphan*/  changedSignal ; 
 int /*<<< orphan*/  g_signal_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setLabel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dateTimeChanged(uiprivDateTimePickerWidget *d)
{
	g_signal_emit(d, changedSignal, 0);
	setLabel(d);
	// TODO fire event here instead?
}