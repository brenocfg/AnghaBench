#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_5__ {scalar_t__ menuPosition; scalar_t__ y; scalar_t__ x; TYPE_1__* parent; } ;
struct TYPE_6__ {size_t curvalue; TYPE_2__ generic; } ;
typedef  TYPE_3__ menulist_s ;
struct TYPE_4__ {scalar_t__ cursor; } ;

/* Variables and functions */
 scalar_t__ PROP_HEIGHT ; 
 int /*<<< orphan*/  UI_DrawProportionalString (scalar_t__,scalar_t__,char*,int,float*) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_SMALLFONT ; 
 char** handicap_items ; 
 float* text_color_highlight ; 
 float* text_color_normal ; 

__attribute__((used)) static void PlayerSettings_DrawHandicap( void *self ) {
	menulist_s		*item;
	qboolean		focus;
	int				style;
	float			*color;

	item = (menulist_s *)self;
	focus = (item->generic.parent->cursor == item->generic.menuPosition);

	style = UI_LEFT|UI_SMALLFONT;
	color = text_color_normal;
	if( focus ) {
		style |= UI_PULSE;
		color = text_color_highlight;
	}

	UI_DrawProportionalString( item->generic.x, item->generic.y, "Handicap", style, color );
	UI_DrawProportionalString( item->generic.x + 64, item->generic.y + PROP_HEIGHT, handicap_items[item->curvalue], style, color );
}