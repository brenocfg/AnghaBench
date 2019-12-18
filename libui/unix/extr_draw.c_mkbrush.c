#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Type; size_t NumStops; TYPE_1__* Stops; int /*<<< orphan*/  OuterRadius; int /*<<< orphan*/  Y1; int /*<<< orphan*/  X1; int /*<<< orphan*/  Y0; int /*<<< orphan*/  X0; int /*<<< orphan*/  A; int /*<<< orphan*/  B; int /*<<< orphan*/  G; int /*<<< orphan*/  R; } ;
typedef  TYPE_2__ uiDrawBrush ;
typedef  int /*<<< orphan*/  cairo_pattern_t ;
struct TYPE_4__ {int /*<<< orphan*/  A; int /*<<< orphan*/  B; int /*<<< orphan*/  G; int /*<<< orphan*/  R; int /*<<< orphan*/  Pos; } ;

/* Variables and functions */
 scalar_t__ CAIRO_STATUS_SUCCESS ; 
 int /*<<< orphan*/  cairo_pattern_add_color_stop_rgba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cairo_pattern_create_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cairo_pattern_create_radial (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cairo_pattern_create_rgba (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cairo_pattern_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_status_to_string (scalar_t__) ; 
#define  uiDrawBrushTypeLinearGradient 130 
#define  uiDrawBrushTypeRadialGradient 129 
#define  uiDrawBrushTypeSolid 128 
 int /*<<< orphan*/  uiprivImplBug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cairo_pattern_t *mkbrush(uiDrawBrush *b)
{
	cairo_pattern_t *pat;
	size_t i;

	switch (b->Type) {
	case uiDrawBrushTypeSolid:
		pat = cairo_pattern_create_rgba(b->R, b->G, b->B, b->A);
		break;
	case uiDrawBrushTypeLinearGradient:
		pat = cairo_pattern_create_linear(b->X0, b->Y0, b->X1, b->Y1);
		break;
	case uiDrawBrushTypeRadialGradient:
		// make the start circle radius 0 to make it a point
		pat = cairo_pattern_create_radial(
			b->X0, b->Y0, 0,
			b->X1, b->Y1, b->OuterRadius);
		break;
//	case uiDrawBrushTypeImage:
	}
	if (cairo_pattern_status(pat) != CAIRO_STATUS_SUCCESS)
		uiprivImplBug("error creating pattern in mkbrush(): %s",
			cairo_status_to_string(cairo_pattern_status(pat)));
	switch (b->Type) {
	case uiDrawBrushTypeLinearGradient:
	case uiDrawBrushTypeRadialGradient:
		for (i = 0; i < b->NumStops; i++)
			cairo_pattern_add_color_stop_rgba(pat,
				b->Stops[i].Pos,
				b->Stops[i].R,
				b->Stops[i].G,
				b->Stops[i].B,
				b->Stops[i].A);
	}
	return pat;
}