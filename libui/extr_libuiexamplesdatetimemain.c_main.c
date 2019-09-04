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
typedef  int /*<<< orphan*/  uiLabel ;
typedef  int /*<<< orphan*/  uiInitOptions ;
typedef  int /*<<< orphan*/  uiGrid ;
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 int /*<<< orphan*/ * dtboth ; 
 int /*<<< orphan*/ * dtdate ; 
 int /*<<< orphan*/ * dttime ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onChanged ; 
 int /*<<< orphan*/  onClicked ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uiAlignCenter ; 
 int /*<<< orphan*/  uiAlignEnd ; 
 int /*<<< orphan*/  uiAlignFill ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDateTimePickerOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeInitError (char const*) ; 
 int /*<<< orphan*/  uiGridAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiGridSetPadded (int /*<<< orphan*/ *,int) ; 
 char* uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewDatePicker () ; 
 int /*<<< orphan*/ * uiNewDateTimePicker () ; 
 int /*<<< orphan*/ * uiNewGrid () ; 
 int /*<<< orphan*/ * uiNewLabel (char*) ; 
 int /*<<< orphan*/ * uiNewTimePicker () ; 
 int /*<<< orphan*/ * uiNewWindow (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowOnClosing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ *,int) ; 

int main(void)
{
	uiInitOptions o;
	const char *err;
	uiWindow *w;
	uiGrid *g;
	uiLabel *l;
	uiButton *b;

	memset(&o, 0, sizeof (uiInitOptions));
	err = uiInit(&o);
	if (err != NULL) {
		fprintf(stderr, "error initializing ui: %s\n", err);
		uiFreeInitError(err);
		return 1;
	}

	w = uiNewWindow("Date / Time", 320, 240, 0);
	uiWindowSetMargined(w, 1);

	g = uiNewGrid();
	uiGridSetPadded(g, 1);
	uiWindowSetChild(w, uiControl(g));

	dtboth = uiNewDateTimePicker();
	dtdate = uiNewDatePicker();
	dttime = uiNewTimePicker();

	uiGridAppend(g, uiControl(dtboth),
		0, 0, 2, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(g, uiControl(dtdate),
		0, 1, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(g, uiControl(dttime),
		1, 1, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);

	l = uiNewLabel("");
	uiGridAppend(g, uiControl(l),
		0, 2, 2, 1,
		1, uiAlignCenter, 0, uiAlignFill);
	uiDateTimePickerOnChanged(dtboth, onChanged, l);
	l = uiNewLabel("");
	uiGridAppend(g, uiControl(l),
		0, 3, 1, 1,
		1, uiAlignCenter, 0, uiAlignFill);
	uiDateTimePickerOnChanged(dtdate, onChanged, l);
	l = uiNewLabel("");
	uiGridAppend(g, uiControl(l),
		1, 3, 1, 1,
		1, uiAlignCenter, 0, uiAlignFill);
	uiDateTimePickerOnChanged(dttime, onChanged, l);

	b = uiNewButton("Now");
	uiButtonOnClicked(b, onClicked, (void *) 1);
	uiGridAppend(g, uiControl(b),
		0, 4, 1, 1,
		1, uiAlignFill, 1, uiAlignEnd);
	b = uiNewButton("Unix epoch");
	uiButtonOnClicked(b, onClicked, (void *) 0);
	uiGridAppend(g, uiControl(b),
		1, 4, 1, 1,
		1, uiAlignFill, 1, uiAlignEnd);

	uiWindowOnClosing(w, onClosing, NULL);
	uiControlShow(uiControl(w));
	uiMain();
	return 0;
}