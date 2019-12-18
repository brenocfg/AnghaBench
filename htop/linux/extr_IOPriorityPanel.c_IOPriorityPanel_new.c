#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  scalar_t__ IOPriority ;

/* Variables and functions */
 int /*<<< orphan*/  Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionBar_newEnterEsc (char*,char*) ; 
#define  IOPRIO_CLASS_BE 129 
#define  IOPRIO_CLASS_RT 128 
 scalar_t__ IOPriority_Idle ; 
 scalar_t__ IOPriority_None ; 
 scalar_t__ IOPriority_tuple (int,int) ; 
 int /*<<< orphan*/  ListItem ; 
 scalar_t__ ListItem_new (char*,scalar_t__) ; 
 int /*<<< orphan*/  Panel_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Panel_new (int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_setHeader (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ Panel_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,char*,int,char*) ; 

Panel* IOPriorityPanel_new(IOPriority currPrio) {
   Panel* this = Panel_new(1, 1, 1, 1, true, Class(ListItem), FunctionBar_newEnterEsc("Set    ", "Cancel "));

   Panel_setHeader(this, "IO Priority:");
   Panel_add(this, (Object*) ListItem_new("None (based on nice)", IOPriority_None));
   if (currPrio == IOPriority_None) Panel_setSelected(this, 0);
   static const struct { int klass; const char* name; } classes[] = {
      { .klass = IOPRIO_CLASS_RT, .name = "Realtime" },
      { .klass = IOPRIO_CLASS_BE, .name = "Best-effort" },
      { .klass = 0, .name = NULL }
   };
   for (int c = 0; classes[c].name; c++) {
      for (int i = 0; i < 8; i++) {
         char name[50];
         xSnprintf(name, sizeof(name)-1, "%s %d %s", classes[c].name, i, i == 0 ? "(High)" : (i == 7 ? "(Low)" : ""));
         IOPriority ioprio = IOPriority_tuple(classes[c].klass, i);
         Panel_add(this, (Object*) ListItem_new(name, ioprio));
         if (currPrio == ioprio) Panel_setSelected(this, Panel_size(this) - 1);
      }
   }
   Panel_add(this, (Object*) ListItem_new("Idle", IOPriority_Idle));
   if (currPrio == IOPriority_Idle) Panel_setSelected(this, Panel_size(this) - 1);
   return this;
}