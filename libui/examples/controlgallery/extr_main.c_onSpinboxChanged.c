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
typedef  int /*<<< orphan*/  uiSpinbox ;

/* Variables and functions */
 int /*<<< orphan*/  pbar ; 
 int /*<<< orphan*/  slider ; 
 int /*<<< orphan*/  uiProgressBarSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiSliderSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiSpinboxValue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void onSpinboxChanged(uiSpinbox *s, void *data)
{
	uiSliderSetValue(slider, uiSpinboxValue(s));
	uiProgressBarSetValue(pbar, uiSpinboxValue(s));
}