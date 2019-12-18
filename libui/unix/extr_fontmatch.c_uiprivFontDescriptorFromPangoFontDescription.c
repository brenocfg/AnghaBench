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
struct TYPE_3__ {size_t Italic; size_t Stretch; int /*<<< orphan*/  Size; int /*<<< orphan*/  Weight; int /*<<< orphan*/  Family; } ;
typedef  TYPE_1__ uiFontDescriptor ;
typedef  scalar_t__ PangoStyle ;
typedef  scalar_t__ PangoStretch ;
typedef  int /*<<< orphan*/  PangoFontDescription ;

/* Variables and functions */
 scalar_t__* pangoItalics ; 
 scalar_t__* pangoStretches ; 
 int /*<<< orphan*/  pango_font_description_get_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ pango_font_description_get_stretch (int /*<<< orphan*/ *) ; 
 scalar_t__ pango_font_description_get_style (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_get_weight (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_units_to_double (int /*<<< orphan*/ ) ; 
 size_t uiTextItalicItalic ; 
 size_t uiTextItalicNormal ; 
 size_t uiTextStretchUltraCondensed ; 
 size_t uiTextStretchUltraExpanded ; 
 int /*<<< orphan*/  uiUnixStrdupText (int /*<<< orphan*/ ) ; 

void uiprivFontDescriptorFromPangoFontDescription(PangoFontDescription *pdesc, uiFontDescriptor *uidesc)
{
	PangoStyle pitalic;
	PangoStretch pstretch;

	uidesc->Family = uiUnixStrdupText(pango_font_description_get_family(pdesc));
	pitalic = pango_font_description_get_style(pdesc);
	// TODO reverse the above misalignment if it is corrected
	uidesc->Weight = pango_font_description_get_weight(pdesc);
	pstretch = pango_font_description_get_stretch(pdesc);
	// absolute size does not matter because, as above, 1 device unit == 1 cairo point
	uidesc->Size = pango_units_to_double(pango_font_description_get_size(pdesc));

	for (uidesc->Italic = uiTextItalicNormal; uidesc->Italic < uiTextItalicItalic; uidesc->Italic++)
		if (pangoItalics[uidesc->Italic] == pitalic)
			break;
	for (uidesc->Stretch = uiTextStretchUltraCondensed; uidesc->Stretch < uiTextStretchUltraExpanded; uidesc->Stretch++)
		if (pangoStretches[uidesc->Stretch] == pstretch)
			break;
}