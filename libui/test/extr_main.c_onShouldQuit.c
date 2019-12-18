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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  shouldQuitItem ; 
 int /*<<< orphan*/  uiControl (void*) ; 
 int /*<<< orphan*/  uiControlDestroy (int /*<<< orphan*/ ) ; 
 scalar_t__ uiMenuItemChecked (int /*<<< orphan*/ ) ; 

int onShouldQuit(void *data)
{
	printf("in onShouldQuit()\n");
	if (uiMenuItemChecked(shouldQuitItem)) {
		uiControlDestroy(uiControl(data));
		return 1;
	}
	return 0;
}