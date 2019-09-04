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
typedef  int /*<<< orphan*/  uiWindow ;

/* Variables and functions */
 int /*<<< orphan*/  fullscreen ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  uiCheckboxSetChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiSpinboxSetValue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiWindowContentSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  uiWindowFullscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static void updatesize(uiWindow *w)
{
	int xp, yp;

	uiWindowContentSize(w, &xp, &yp);
	uiSpinboxSetValue(width, xp);
	uiSpinboxSetValue(height, yp);
	// TODO on OS X this is updated AFTER sending the size change, not before
	uiCheckboxSetChecked(fullscreen, uiWindowFullscreen(w));
}