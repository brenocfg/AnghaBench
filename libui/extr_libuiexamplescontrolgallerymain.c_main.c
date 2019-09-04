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
typedef  int /*<<< orphan*/  uiTab ;
typedef  int /*<<< orphan*/  uiInitOptions ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * mainwin ; 
 int /*<<< orphan*/  makeBasicControlsPage () ; 
 int /*<<< orphan*/  makeDataChoosersPage () ; 
 int /*<<< orphan*/  makeNumbersPage () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  onShouldQuit ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeInitError (char const*) ; 
 char* uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/ * uiNewTab () ; 
 int /*<<< orphan*/ * uiNewWindow (char*,int,int,int) ; 
 int /*<<< orphan*/  uiOnShouldQuit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiTabAppend (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTabSetMargined (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiWindowOnClosing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ *,int) ; 

int main(void)
{
	uiInitOptions options;
	const char *err;
	uiTab *tab;

	memset(&options, 0, sizeof (uiInitOptions));
	err = uiInit(&options);
	if (err != NULL) {
		fprintf(stderr, "error initializing libui: %s", err);
		uiFreeInitError(err);
		return 1;
	}

	mainwin = uiNewWindow("libui Control Gallery", 640, 480, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);
	uiOnShouldQuit(onShouldQuit, mainwin);

	tab = uiNewTab();
	uiWindowSetChild(mainwin, uiControl(tab));
	uiWindowSetMargined(mainwin, 1);

	uiTabAppend(tab, "Basic Controls", makeBasicControlsPage());
	uiTabSetMargined(tab, 0, 1);

	uiTabAppend(tab, "Numbers and Lists", makeNumbersPage());
	uiTabSetMargined(tab, 1, 1);

	uiTabAppend(tab, "Data Choosers", makeDataChoosersPage());
	uiTabSetMargined(tab, 2, 1);

	uiControlShow(uiControl(mainwin));
	uiMain();
	return 0;
}