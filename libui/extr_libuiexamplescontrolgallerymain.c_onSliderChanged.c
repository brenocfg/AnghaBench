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
typedef  int /*<<< orphan*/  uiSlider ;

/* Variables and functions */
 int /*<<< orphan*/  pbar ; 
 int /*<<< orphan*/  spinbox ; 
 int /*<<< orphan*/  uiProgressBarSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiSliderValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiSpinboxSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void onSliderChanged(uiSlider *s, void *data)
{
	uiSpinboxSetValue(spinbox, uiSliderValue(s));
	uiProgressBarSetValue(pbar, uiSliderValue(s));
}