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
struct TYPE_3__ {int /*<<< orphan*/  Stretch; int /*<<< orphan*/  Italic; int /*<<< orphan*/  Weight; int /*<<< orphan*/  Size; int /*<<< orphan*/  Family; } ;
typedef  TYPE_1__ uiFontDescriptor ;
typedef  int /*<<< orphan*/  PangoFontDescription ;

/* Variables and functions */
 int /*<<< orphan*/ * pango_font_description_new () ; 
 int /*<<< orphan*/  pango_font_description_set_family (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_stretch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_style (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_units_from_double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivItalicToPangoStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivStretchToPangoStretch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivWeightToPangoWeight (int /*<<< orphan*/ ) ; 

PangoFontDescription *uiprivFontDescriptorToPangoFontDescription(const uiFontDescriptor *uidesc)
{
	PangoFontDescription *desc;

	desc = pango_font_description_new();
	pango_font_description_set_family(desc, uidesc->Family);
	// see https://developer.gnome.org/pango/1.30/pango-Fonts.html#pango-font-description-set-size and https://developer.gnome.org/pango/1.30/pango-Glyph-Storage.html#pango-units-from-double
	pango_font_description_set_size(desc, pango_units_from_double(uidesc->Size));
	pango_font_description_set_weight(desc, uiprivWeightToPangoWeight(uidesc->Weight));
	pango_font_description_set_style(desc, uiprivItalicToPangoStyle(uidesc->Italic));
	pango_font_description_set_stretch(desc, uiprivStretchToPangoStretch(uidesc->Stretch));
	return desc;
}