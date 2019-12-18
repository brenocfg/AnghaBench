#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qhandle_t ;
struct TYPE_14__ {int endPos; int startPos; scalar_t__ elementStyle; int elementWidth; int elementHeight; float drawPadding; scalar_t__ numColumns; TYPE_2__* columnInfo; } ;
typedef  TYPE_5__ listBoxDef_t ;
struct TYPE_13__ {int x; int y; int h; float w; } ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  outlineColor; TYPE_4__ rect; int /*<<< orphan*/  foreColor; int /*<<< orphan*/  borderColor; int /*<<< orphan*/  borderSize; } ;
struct TYPE_15__ {int cursorPos; TYPE_3__ window; int /*<<< orphan*/  textStyle; int /*<<< orphan*/  textscale; int /*<<< orphan*/  special; scalar_t__ typeData; } ;
typedef  TYPE_6__ itemDef_t ;
struct TYPE_10__ {scalar_t__ scrollBarArrowLeft; scalar_t__ scrollBar; scalar_t__ scrollBarArrowRight; scalar_t__ scrollBarThumb; scalar_t__ scrollBarArrowUp; scalar_t__ scrollBarArrowDown; } ;
struct TYPE_16__ {int (* feederCount ) (int /*<<< orphan*/ ) ;scalar_t__ (* feederItemImage ) (int /*<<< orphan*/ ,int) ;char* (* feederItemText ) (int /*<<< orphan*/ ,int,int,scalar_t__*) ;int /*<<< orphan*/  (* fillRect ) (float,float,float,float,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* drawText ) (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* drawHandlePic ) (float,float,int,int,scalar_t__) ;int /*<<< orphan*/  (* drawRect ) (float,float,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ Assets; } ;
struct TYPE_11__ {float pos; int width; int /*<<< orphan*/  maxChars; } ;

/* Variables and functions */
 TYPE_9__* DC ; 
 float Item_ListBox_ThumbDrawPosition (TYPE_6__*) ; 
 scalar_t__ LISTBOX_IMAGE ; 
 int SCROLLBAR_SIZE ; 
 int WINDOW_HORIZONTAL ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (float,float,int,float,scalar_t__) ; 
 int /*<<< orphan*/  stub11 (float,float,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub12 (float,float,int,int,scalar_t__) ; 
 scalar_t__ stub13 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (float,float,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub15 (float,float,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub16 (int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub17 (float,float,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub18 (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub19 (int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (float,float,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub20 (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (float,float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (float,float,float,int,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (float,float,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (float,float,int,int,scalar_t__) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (float,float,int,int,scalar_t__) ; 
 int /*<<< orphan*/  stub8 (float,float,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (float,float,int,int,scalar_t__) ; 

void Item_ListBox_Paint(itemDef_t *item) {
	float x, y, size, thumb;
	int	count, i;
	qhandle_t image;
	qhandle_t optionalImage;
	listBoxDef_t *listPtr = (listBoxDef_t*)item->typeData;

	// the listbox is horizontal or vertical and has a fixed size scroll bar going either direction
	// elements are enumerated from the DC and either text or image handles are acquired from the DC as well
	// textscale is used to size the text, textalignx and textaligny are used to size image elements
	// there is no clipping available so only the last completely visible item is painted
	count = DC->feederCount(item->special);
	// default is vertical if horizontal flag is not here
	if (item->window.flags & WINDOW_HORIZONTAL) {
		// draw scrollbar in bottom of the window
		// bar
		x = item->window.rect.x + 1;
		y = item->window.rect.y + item->window.rect.h - SCROLLBAR_SIZE - 1;
		DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowLeft);
		x += SCROLLBAR_SIZE - 1;
		size = item->window.rect.w - (SCROLLBAR_SIZE * 2);
		DC->drawHandlePic(x, y, size+1, SCROLLBAR_SIZE, DC->Assets.scrollBar);
		x += size - 1;
		DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowRight);
		// thumb
		thumb = Item_ListBox_ThumbDrawPosition(item);//Item_ListBox_ThumbPosition(item);
		if (thumb > x - SCROLLBAR_SIZE - 1) {
			thumb = x - SCROLLBAR_SIZE - 1;
		}
		DC->drawHandlePic(thumb, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarThumb);
		//
		listPtr->endPos = listPtr->startPos;
		size = item->window.rect.w - 2;
		// items
		// size contains max available space
		if (listPtr->elementStyle == LISTBOX_IMAGE) {
			// fit = 0;
			x = item->window.rect.x + 1;
			y = item->window.rect.y + 1;
			for (i = listPtr->startPos; i < count; i++) {
				// always draw at least one
				// which may overdraw the box if it is too small for the element
				image = DC->feederItemImage(item->special, i);
				if (image) {
					DC->drawHandlePic(x+1, y+1, listPtr->elementWidth - 2, listPtr->elementHeight - 2, image);
				}

				if (i == item->cursorPos) {
					DC->drawRect(x, y, listPtr->elementWidth-1, listPtr->elementHeight-1, item->window.borderSize, item->window.borderColor);
				}

				size -= listPtr->elementWidth;
				if (size < listPtr->elementWidth) {
					listPtr->drawPadding = size; //listPtr->elementWidth - size;
					break;
				}
				x += listPtr->elementWidth;
				listPtr->endPos++;
				// fit++;
			}
		} else {
			//
		}
	} else {
		// draw scrollbar to right side of the window
		x = item->window.rect.x + item->window.rect.w - SCROLLBAR_SIZE - 1;
		y = item->window.rect.y + 1;
		DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowUp);
		y += SCROLLBAR_SIZE - 1;

		listPtr->endPos = listPtr->startPos;
		size = item->window.rect.h - (SCROLLBAR_SIZE * 2);
		DC->drawHandlePic(x, y, SCROLLBAR_SIZE, size+1, DC->Assets.scrollBar);
		y += size - 1;
		DC->drawHandlePic(x, y, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarArrowDown);
		// thumb
		thumb = Item_ListBox_ThumbDrawPosition(item);//Item_ListBox_ThumbPosition(item);
		if (thumb > y - SCROLLBAR_SIZE - 1) {
			thumb = y - SCROLLBAR_SIZE - 1;
		}
		DC->drawHandlePic(x, thumb, SCROLLBAR_SIZE, SCROLLBAR_SIZE, DC->Assets.scrollBarThumb);

		// adjust size for item painting
		size = item->window.rect.h - 2;
		if (listPtr->elementStyle == LISTBOX_IMAGE) {
			// fit = 0;
			x = item->window.rect.x + 1;
			y = item->window.rect.y + 1;
			for (i = listPtr->startPos; i < count; i++) {
				// always draw at least one
				// which may overdraw the box if it is too small for the element
				image = DC->feederItemImage(item->special, i);
				if (image) {
					DC->drawHandlePic(x+1, y+1, listPtr->elementWidth - 2, listPtr->elementHeight - 2, image);
				}

				if (i == item->cursorPos) {
					DC->drawRect(x, y, listPtr->elementWidth - 1, listPtr->elementHeight - 1, item->window.borderSize, item->window.borderColor);
				}

				listPtr->endPos++;
				size -= listPtr->elementWidth;
				if (size < listPtr->elementHeight) {
					listPtr->drawPadding = listPtr->elementHeight - size;
					break;
				}
				y += listPtr->elementHeight;
				// fit++;
			}
		} else {
			x = item->window.rect.x + 1;
			y = item->window.rect.y + 1;
			for (i = listPtr->startPos; i < count; i++) {
				const char *text;
				// always draw at least one
				// which may overdraw the box if it is too small for the element

				if (listPtr->numColumns > 0) {
					int j;
					for (j = 0; j < listPtr->numColumns; j++) {
						text = DC->feederItemText(item->special, i, j, &optionalImage);
						if (optionalImage >= 0) {
							DC->drawHandlePic(x + 4 + listPtr->columnInfo[j].pos, y - 1 + listPtr->elementHeight / 2, listPtr->columnInfo[j].width, listPtr->columnInfo[j].width, optionalImage);
						} else if (text) {
							DC->drawText(x + 4 + listPtr->columnInfo[j].pos, y + listPtr->elementHeight, item->textscale, item->window.foreColor, text, 0, listPtr->columnInfo[j].maxChars, item->textStyle);
						}
					}
				} else {
					text = DC->feederItemText(item->special, i, 0, &optionalImage);
					if (optionalImage >= 0) {
						//DC->drawHandlePic(x + 4 + listPtr->elementHeight, y, listPtr->columnInfo[j].width, listPtr->columnInfo[j].width, optionalImage);
					} else if (text) {
						DC->drawText(x + 4, y + listPtr->elementHeight, item->textscale, item->window.foreColor, text, 0, 0, item->textStyle);
					}
				}

				if (i == item->cursorPos) {
					DC->fillRect(x + 2, y + 2, item->window.rect.w - SCROLLBAR_SIZE - 4, listPtr->elementHeight, item->window.outlineColor);
				}

				size -= listPtr->elementHeight;
				if (size < listPtr->elementHeight) {
					listPtr->drawPadding = listPtr->elementHeight - size;
					break;
				}
				listPtr->endPos++;
				y += listPtr->elementHeight;
				// fit++;
			}
		}
	}
}