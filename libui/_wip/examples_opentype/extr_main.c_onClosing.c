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
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlHide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiQuit () ; 

__attribute__((used)) static int onClosing(uiWindow *w, void *data)
{
	// TODO change the others to be like this? (the others destroy here rather than later)
	// TODO move this below uiQuit()?
	uiControlHide(uiControl(w));
	uiQuit();
	return 0;
}