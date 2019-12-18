#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_1__* pl; int /*<<< orphan*/  height; } ;
struct TYPE_23__ {int y; } ;
struct TYPE_22__ {int pid; } ;
struct TYPE_21__ {int allowFocusChange; } ;
struct TYPE_20__ {int /*<<< orphan*/ * settings; TYPE_6__* header; TYPE_5__* panel; } ;
struct TYPE_19__ {int following; } ;
typedef  TYPE_2__ State ;
typedef  int /*<<< orphan*/  Settings ;
typedef  TYPE_3__ ScreenManager ;
typedef  TYPE_4__ Process ;
typedef  TYPE_5__ Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  MainPanel ;
typedef  TYPE_6__ Header ;

/* Variables and functions */
 int /*<<< orphan*/  COLS ; 
 int /*<<< orphan*/  HORIZONTAL ; 
 int LINES ; 
 int MainPanel_selectedPid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Panel_getSelected (TYPE_5__*) ; 
 int /*<<< orphan*/  Panel_move (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Panel_resize (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ScreenManager_add (TYPE_3__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ScreenManager_delete (TYPE_3__*) ; 
 TYPE_3__* ScreenManager_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ScreenManager_run (TYPE_3__*,TYPE_5__**,int*) ; 
 int /*<<< orphan*/  beep () ; 

Object* Action_pickFromVector(State* st, Panel* list, int x) {
   Panel* panel = st->panel;
   Header* header = st->header;
   Settings* settings = st->settings;
   
   int y = panel->y;
   ScreenManager* scr = ScreenManager_new(0, header->height, 0, -1, HORIZONTAL, header, settings, false);
   scr->allowFocusChange = false;
   ScreenManager_add(scr, list, x - 1);
   ScreenManager_add(scr, panel, -1);
   Panel* panelFocus;
   int ch;
   bool unfollow = false;
   int pid = MainPanel_selectedPid((MainPanel*)panel);
   if (header->pl->following == -1) {
      header->pl->following = pid;
      unfollow = true;
   }
   ScreenManager_run(scr, &panelFocus, &ch);
   if (unfollow) {
      header->pl->following = -1;
   }
   ScreenManager_delete(scr);
   Panel_move(panel, 0, y);
   Panel_resize(panel, COLS, LINES-y-1);
   if (panelFocus == list && ch == 13) {
      Process* selected = (Process*)Panel_getSelected(panel);
      if (selected && selected->pid == pid)
         return Panel_getSelected(list);
      else
         beep();
   }
   return NULL;
}