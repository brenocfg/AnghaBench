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
struct TYPE_3__ {int /*<<< orphan*/  panel; } ;
typedef  TYPE_1__ State ;
typedef  int /*<<< orphan*/  Process ;
typedef  int /*<<< orphan*/  OpenFilesScreen ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  InfoScreen ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_enableDelay () ; 
 int HTOP_OK ; 
 int HTOP_REDRAW_BAR ; 
 int HTOP_REFRESH ; 
 int /*<<< orphan*/  InfoScreen_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenFilesScreen_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenFilesScreen_new (int /*<<< orphan*/ *) ; 
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear () ; 

__attribute__((used)) static Htop_Reaction actionLsof(State* st) {
   Process* p = (Process*) Panel_getSelected(st->panel);
   if (!p) return HTOP_OK;
   OpenFilesScreen* ofs = OpenFilesScreen_new(p);
   InfoScreen_run((InfoScreen*)ofs);
   OpenFilesScreen_delete((Object*)ofs);
   clear();
   CRT_enableDelay();
   return HTOP_REFRESH | HTOP_REDRAW_BAR;
}