#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; int /*<<< orphan*/  panels; TYPE_3__* header; } ;
struct TYPE_13__ {TYPE_5__* scr; TYPE_1__* settings; } ;
struct TYPE_12__ {int /*<<< orphan*/  height; } ;
struct TYPE_11__ {int /*<<< orphan*/  header; } ;
struct TYPE_10__ {int colorScheme; int changed; } ;
typedef  TYPE_2__ Panel ;
typedef  TYPE_3__ Header ;
typedef  scalar_t__ HandlerResult ;
typedef  TYPE_4__ ColorsPanel ;
typedef  int /*<<< orphan*/  CheckItem ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 int /*<<< orphan*/  CRT_setColors (int) ; 
 int /*<<< orphan*/  CheckItem_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** ColorSchemeNames ; 
 scalar_t__ HANDLED ; 
 int /*<<< orphan*/  Header_draw (TYPE_3__ const*) ; 
 scalar_t__ IGNORED ; 
#define  KEY_ENTER 130 
#define  KEY_MOUSE 129 
#define  KEY_RECLICK 128 
 size_t PANEL_HEADER_FOCUS ; 
 size_t PANEL_HEADER_UNFOCUS ; 
 scalar_t__ Panel_get (TYPE_2__*,int) ; 
 int Panel_getSelectedIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  RichString_setAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenManager_resize (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear () ; 

__attribute__((used)) static HandlerResult ColorsPanel_eventHandler(Panel* super, int ch) {
   ColorsPanel* this = (ColorsPanel*) super;
   
   HandlerResult result = IGNORED;
   int mark = Panel_getSelectedIndex(super);

   switch(ch) {
   case 0x0a:
   case 0x0d:
   case KEY_ENTER:
   case KEY_MOUSE:
   case KEY_RECLICK:
   case ' ':
      for (int i = 0; ColorSchemeNames[i] != NULL; i++)
         CheckItem_set((CheckItem*)Panel_get(super, i), false);
      CheckItem_set((CheckItem*)Panel_get(super, mark), true);
      this->settings->colorScheme = mark;
      result = HANDLED;
   }

   if (result == HANDLED) {
      this->settings->changed = true;
      const Header* header = this->scr->header;
      CRT_setColors(mark);
      clear();
      Panel* menu = (Panel*) Vector_get(this->scr->panels, 0);
      Header_draw(header);
      RichString_setAttr(&(super->header), CRT_colors[PANEL_HEADER_FOCUS]);
      RichString_setAttr(&(menu->header), CRT_colors[PANEL_HEADER_UNFOCUS]);
      ScreenManager_resize(this->scr, this->scr->x1, header->height, this->scr->x2, this->scr->y2);
   }
   return result;
}