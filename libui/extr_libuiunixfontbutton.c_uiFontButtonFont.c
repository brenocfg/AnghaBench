#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiFontDescriptor ;
struct TYPE_3__ {int /*<<< orphan*/  fc; } ;
typedef  TYPE_1__ uiFontButton ;
typedef  int /*<<< orphan*/  PangoFontDescription ;

/* Variables and functions */
 int /*<<< orphan*/ * gtk_font_chooser_get_font_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivFontDescriptorFromPangoFontDescription (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uiFontButtonFont(uiFontButton *b, uiFontDescriptor *desc)
{
	PangoFontDescription *pdesc;

	pdesc = gtk_font_chooser_get_font_desc(b->fc);
	uiprivFontDescriptorFromPangoFontDescription(pdesc, desc);
	// pdesc is transfer-full and thus is a copy
	pango_font_description_free(pdesc);
}