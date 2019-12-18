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
typedef  int /*<<< orphan*/  uiDrawFontFamilies ;
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 char* uiDrawFontFamiliesFamily (int /*<<< orphan*/ *,int) ; 
 int uiDrawFontFamiliesNumFamilies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFreeFontFamilies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawListFontFamilies () ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 
 int /*<<< orphan*/  uiMultilineEntry (void*) ; 
 int /*<<< orphan*/  uiMultilineEntryAppend (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiMultilineEntrySetText (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void onListFonts(uiButton *b, void *data)
{
	uiDrawFontFamilies *ff;
	char *this;
	int i, n;

	uiMultilineEntrySetText(uiMultilineEntry(data), "");
	ff = uiDrawListFontFamilies();
	n = uiDrawFontFamiliesNumFamilies(ff);
	for (i = 0; i < n; i++) {
		this = uiDrawFontFamiliesFamily(ff, i);
		uiMultilineEntryAppend(uiMultilineEntry(data), this);
		uiMultilineEntryAppend(uiMultilineEntry(data), "\n");
		uiFreeText(this);
	}
	uiDrawFreeFontFamilies(ff);
}