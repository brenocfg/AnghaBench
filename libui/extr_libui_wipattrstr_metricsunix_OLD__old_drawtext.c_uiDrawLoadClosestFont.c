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
struct TYPE_3__ {int Size; size_t Weight; size_t Italic; size_t Stretch; int /*<<< orphan*/  Family; } ;
typedef  TYPE_1__ uiDrawTextFontDescriptor ;
typedef  int /*<<< orphan*/  uiDrawTextFont ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  PangoFontDescription ;
typedef  int /*<<< orphan*/  PangoFont ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PANGO_SCALE ; 
 int /*<<< orphan*/ * mkTextFont (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pangoDescToPangoFont (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pangoItalics ; 
 int /*<<< orphan*/ * pangoStretches ; 
 int /*<<< orphan*/ * pangoWeights ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_font_description_new () ; 
 int /*<<< orphan*/  pango_font_description_set_family (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_stretch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_style (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_set_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uiDrawTextFont *uiDrawLoadClosestFont(const uiDrawTextFontDescriptor *desc)
{
	PangoFont *f;
	PangoFontDescription *pdesc;

	pdesc = pango_font_description_new();
	pango_font_description_set_family(pdesc,
		desc->Family);
	pango_font_description_set_size(pdesc,
		(gint) (desc->Size * PANGO_SCALE));
	pango_font_description_set_weight(pdesc,
		pangoWeights[desc->Weight]);
	pango_font_description_set_style(pdesc,
		pangoItalics[desc->Italic]);
	pango_font_description_set_stretch(pdesc,
		pangoStretches[desc->Stretch]);
	f = pangoDescToPangoFont(pdesc);
	pango_font_description_free(pdesc);
	return mkTextFont(f, FALSE);			// we hold the initial reference; no need to ref
}