#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; int y; int flags; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {float* color; int style; int /*<<< orphan*/  string; TYPE_1__ generic; } ;
typedef  TYPE_2__ menutext_s ;

/* Variables and functions */
 TYPE_2__* Menu_ItemAtCursor (int /*<<< orphan*/ ) ; 
 int QMF_GRAYED ; 
 int QMF_PULSEIFFOCUS ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,int /*<<< orphan*/ ,int,float*) ; 
 int UI_INVERSE ; 
 int UI_PULSE ; 
 float* color_blue ; 

__attribute__((used)) static void PText_Draw( menutext_s *t )
{
	int		x;
	int		y;
	float *	color;
	int		style;

	x = t->generic.x;
	y = t->generic.y;

	if (t->generic.flags & QMF_GRAYED)
		color = color_blue; //text_color_disabled
	else
		color = t->color;

	style = t->style;
	if( t->generic.flags & QMF_PULSEIFFOCUS ) {
		if( Menu_ItemAtCursor( t->generic.parent ) == t ) {
			style |= UI_PULSE;
		}
		else {
			style |= UI_INVERSE; //UI_LEFT - changed to stop text
		}
	}

	UI_DrawProportionalString( x, y, t->string, style, color );
}