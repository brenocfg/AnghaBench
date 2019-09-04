#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_6__ {int x; int y; scalar_t__ menuPosition; int flags; int /*<<< orphan*/  name; TYPE_1__* parent; } ;
struct TYPE_7__ {scalar_t__ maxvalue; scalar_t__ minvalue; float range; float curvalue; TYPE_2__ generic; } ;
typedef  TYPE_3__ menuslider_s ;
struct TYPE_5__ {scalar_t__ cursor; } ;

/* Variables and functions */
 int QMF_GRAYED ; 
 int SLIDER_RANGE ; 
 int SMALLCHAR_WIDTH ; 
 int /*<<< orphan*/  UI_DrawHandlePic (int,int,int,int,int) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,int /*<<< orphan*/ ,int,float*) ; 
 int UI_PULSE ; 
 int UI_RIGHT ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  UI_SetColor (float*) ; 
 int sliderBar ; 
 int sliderButton_0 ; 
 int sliderButton_1 ; 
 float* text_color_disabled ; 
 float* text_color_highlight ; 
 float* text_color_normal ; 

__attribute__((used)) static void Slider_Draw( menuslider_s *s ) {
	int			x;
	int			y;
	int			style;
	float		*color;
	int			button;
	qboolean	focus;
	
	x =	s->generic.x;
	y = s->generic.y;
	focus = (s->generic.parent->cursor == s->generic.menuPosition);

	if( s->generic.flags & QMF_GRAYED ) {
		color = text_color_disabled;
		style = UI_SMALLFONT;
	}
	else if( focus ) {
		color  = text_color_highlight;
		style = UI_SMALLFONT | UI_PULSE;
	}
	else {
		color = text_color_normal;
		style = UI_SMALLFONT;
	}

	// draw label
	UI_DrawString( x - SMALLCHAR_WIDTH, y, s->generic.name, UI_RIGHT|style, color );

	// draw slider
	UI_SetColor( color );
	UI_DrawHandlePic( x + SMALLCHAR_WIDTH, y, 96, 16, sliderBar );
	UI_SetColor( NULL );

	// clamp thumb
	if( s->maxvalue > s->minvalue )	{
		s->range = ( s->curvalue - s->minvalue ) / ( float ) ( s->maxvalue - s->minvalue );
		if( s->range < 0 ) {
			s->range = 0;
		}
		else if( s->range > 1) {
			s->range = 1;
		}
	}
	else {
		s->range = 0;
	}

	// draw thumb
	if( style & UI_PULSE) {
		button = sliderButton_1;
	}
	else {
		button = sliderButton_0;
	}

	UI_DrawHandlePic( (int)( x + 2*SMALLCHAR_WIDTH + (SLIDER_RANGE-1)*SMALLCHAR_WIDTH* s->range ) - 2, y - 2, 12, 20, button );
}