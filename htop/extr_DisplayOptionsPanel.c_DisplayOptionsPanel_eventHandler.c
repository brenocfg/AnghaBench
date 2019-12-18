#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; TYPE_2__* header; } ;
struct TYPE_10__ {TYPE_4__* scr; TYPE_1__* settings; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; } ;
struct TYPE_8__ {int changed; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  TYPE_2__ Header ;
typedef  scalar_t__ HandlerResult ;
typedef  TYPE_3__ DisplayOptionsPanel ;
typedef  int /*<<< orphan*/  CheckItem ;

/* Variables and functions */
 int /*<<< orphan*/  CheckItem_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckItem_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ HANDLED ; 
 int /*<<< orphan*/  Header_calculateHeight (TYPE_2__*) ; 
 int /*<<< orphan*/  Header_draw (TYPE_2__ const*) ; 
 int /*<<< orphan*/  Header_reinit (TYPE_2__*) ; 
 scalar_t__ IGNORED ; 
#define  KEY_ENTER 130 
#define  KEY_MOUSE 129 
#define  KEY_RECLICK 128 
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScreenManager_resize (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HandlerResult DisplayOptionsPanel_eventHandler(Panel* super, int ch) {
   DisplayOptionsPanel* this = (DisplayOptionsPanel*) super;
   
   HandlerResult result = IGNORED;
   CheckItem* selected = (CheckItem*) Panel_getSelected(super);

   switch(ch) {
   case 0x0a:
   case 0x0d:
   case KEY_ENTER:
   case KEY_MOUSE:
   case KEY_RECLICK:
   case ' ':
      CheckItem_set(selected, ! (CheckItem_get(selected)) );
      result = HANDLED;
   }

   if (result == HANDLED) {
      this->settings->changed = true;
      const Header* header = this->scr->header;
      Header_calculateHeight((Header*) header);
      Header_reinit((Header*) header);
      Header_draw(header);
      ScreenManager_resize(this->scr, this->scr->x1, header->height, this->scr->x2, this->scr->y2);
   }
   return result;
}