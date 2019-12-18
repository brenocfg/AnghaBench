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
typedef  int /*<<< orphan*/  TraceScreen ;
struct TYPE_3__ {int /*<<< orphan*/  panel; } ;
typedef  TYPE_1__ State ;
typedef  int /*<<< orphan*/  Process ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  InfoScreen ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_enableDelay () ; 
 int HTOP_OK ; 
 int HTOP_REDRAW_BAR ; 
 int HTOP_REFRESH ; 
 int /*<<< orphan*/  InfoScreen_run (int /*<<< orphan*/ *) ; 
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TraceScreen_delete (int /*<<< orphan*/ *) ; 
 int TraceScreen_forkTracer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TraceScreen_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear () ; 

__attribute__((used)) static Htop_Reaction actionStrace(State* st) {
   Process* p = (Process*) Panel_getSelected(st->panel);
   if (!p) return HTOP_OK;
   TraceScreen* ts = TraceScreen_new(p);
   bool ok = TraceScreen_forkTracer(ts);
   if (ok) {
      InfoScreen_run((InfoScreen*)ts);
   }
   TraceScreen_delete((Object*)ts);
   clear();
   CRT_enableDelay();
   return HTOP_REFRESH | HTOP_REDRAW_BAR;
}