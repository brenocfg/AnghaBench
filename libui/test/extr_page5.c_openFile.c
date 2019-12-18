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
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 
 int /*<<< orphan*/  uiLabel (void*) ; 
 int /*<<< orphan*/  uiLabelSetText (int /*<<< orphan*/ ,char*) ; 
 char* uiOpenFile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void openFile(uiButton *b, void *data)
{
	char *fn;

	fn = uiOpenFile(parent);
	if (fn == NULL)
		uiLabelSetText(uiLabel(data), "(cancelled)");
	else {
		uiLabelSetText(uiLabel(data), fn);
		uiFreeText(fn);
	}
}