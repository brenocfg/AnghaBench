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
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_SAVE ; 
 char* filedialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  windowWindow (int /*<<< orphan*/ *) ; 

char *uiSaveFile(uiWindow *parent)
{
	return filedialog(windowWindow(parent), GTK_FILE_CHOOSER_ACTION_SAVE, "_Save");
}