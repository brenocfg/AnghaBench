#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_10__ {float y; scalar_t__ x; } ;
struct TYPE_9__ {int w; } ;
struct TYPE_12__ {TYPE_1__ rect; } ;
struct TYPE_11__ {char* text; float textaligny; scalar_t__ textalignment; int /*<<< orphan*/  textStyle; int /*<<< orphan*/  textscale; TYPE_2__ textRect; TYPE_4__ window; scalar_t__ textalignx; int /*<<< orphan*/ * cvar; } ;
typedef  TYPE_3__ itemDef_t ;
struct TYPE_13__ {int (* textWidth ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* drawText ) (scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* getCVarString ) (int /*<<< orphan*/ *,char*,int) ;} ;

/* Variables and functions */
 TYPE_8__* DC ; 
 scalar_t__ ITEM_ALIGN_CENTER ; 
 scalar_t__ ITEM_ALIGN_LEFT ; 
 scalar_t__ ITEM_ALIGN_RIGHT ; 
 int /*<<< orphan*/  Item_SetTextExtents (TYPE_3__*,int*,int*,char const*) ; 
 int /*<<< orphan*/  Item_TextColor (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ToWindowCoords (scalar_t__*,float*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,int) ; 
 int stub2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Item_Text_AutoWrapped_Paint(itemDef_t *item) {
	char text[1024];
	const char *p, *textPtr, *newLinePtr;
	char buff[1024];
	int width, height, len, textWidth, newLine, newLineWidth;
	float y;
	vec4_t color;

	textWidth = 0;
	newLinePtr = NULL;

	if (item->text == NULL) {
		if (item->cvar == NULL) {
			return;
		}
		else {
			DC->getCVarString(item->cvar, text, sizeof(text));
			textPtr = text;
		}
	}
	else {
		textPtr = item->text;
	}
	if (*textPtr == '\0') {
		return;
	}
	Item_TextColor(item, &color);
	Item_SetTextExtents(item, &width, &height, textPtr);

	y = item->textaligny;
	len = 0;
	buff[0] = '\0';
	newLine = 0;
	newLineWidth = 0;
	p = textPtr;
	while (p) {
		if (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\0') {
			newLine = len;
			newLinePtr = p+1;
			newLineWidth = textWidth;
		}
		textWidth = DC->textWidth(buff, item->textscale, 0);
		if ( (newLine && textWidth > item->window.rect.w) || *p == '\n' || *p == '\0') {
			if (len) {
				if (item->textalignment == ITEM_ALIGN_LEFT) {
					item->textRect.x = item->textalignx;
				} else if (item->textalignment == ITEM_ALIGN_RIGHT) {
					item->textRect.x = item->textalignx - newLineWidth;
				} else if (item->textalignment == ITEM_ALIGN_CENTER) {
					item->textRect.x = item->textalignx - newLineWidth / 2;
				}
				item->textRect.y = y;
				ToWindowCoords(&item->textRect.x, &item->textRect.y, &item->window);
				//
				buff[newLine] = '\0';
				DC->drawText(item->textRect.x, item->textRect.y, item->textscale, color, buff, 0, 0, item->textStyle);
			}
			if (*p == '\0') {
				break;
			}
			//
			y += height + 5;
			p = newLinePtr;
			len = 0;
			newLine = 0;
			newLineWidth = 0;
			continue;
		}
		buff[len++] = *p++;
		buff[len] = '\0';
	}
}