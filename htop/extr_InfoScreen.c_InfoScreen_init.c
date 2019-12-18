#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* items; } ;
struct TYPE_8__ {TYPE_3__* display; int /*<<< orphan*/  lines; int /*<<< orphan*/  inc; int /*<<< orphan*/ * process; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Process ;
typedef  TYPE_2__ InfoScreen ;
typedef  int /*<<< orphan*/  FunctionBar ;

/* Variables and functions */
 int /*<<< orphan*/  COLS ; 
 int /*<<< orphan*/  Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_SIZE ; 
 int /*<<< orphan*/ * FunctionBar_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IncSet_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InfoScreenEvents ; 
 int /*<<< orphan*/  InfoScreenFunctions ; 
 int /*<<< orphan*/  InfoScreenKeys ; 
 int /*<<< orphan*/  ListItem ; 
 TYPE_3__* Panel_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Panel_setHeader (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  Vector_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

InfoScreen* InfoScreen_init(InfoScreen* this, Process* process, FunctionBar* bar, int height, char* panelHeader) {
   this->process = process;
   if (!bar) {
      bar = FunctionBar_new(InfoScreenFunctions, InfoScreenKeys, InfoScreenEvents);
   }
   this->display = Panel_new(0, 1, COLS, height, false, Class(ListItem), bar);
   this->inc = IncSet_new(bar);
   this->lines = Vector_new(this->display->items->type, true, DEFAULT_SIZE);
   Panel_setHeader(this->display, panelHeader);
   return this;
}