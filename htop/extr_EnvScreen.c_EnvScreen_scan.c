#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  lines; TYPE_1__* process; TYPE_2__* display; } ;
struct TYPE_10__ {int /*<<< orphan*/  items; } ;
struct TYPE_9__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ Panel ;
typedef  TYPE_3__ InfoScreen ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_dropPrivileges () ; 
 int /*<<< orphan*/  CRT_restorePrivileges () ; 
 int /*<<< orphan*/  InfoScreen_addLine (TYPE_3__*,char*) ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_getSelectedIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  Panel_prune (TYPE_2__*) ; 
 int /*<<< orphan*/  Panel_setSelected (TYPE_2__*,int) ; 
 char* Platform_getProcessEnv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_insertionSort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strrchr (char*,int /*<<< orphan*/ ) ; 

void EnvScreen_scan(InfoScreen* this) {
   Panel* panel = this->display;
   int idx = MAX(Panel_getSelectedIndex(panel), 0);

   Panel_prune(panel);

   CRT_dropPrivileges();
   char* env = Platform_getProcessEnv(this->process->pid);
   CRT_restorePrivileges();
   if (env) {
      for (char *p = env; *p; p = strrchr(p, 0)+1)
         InfoScreen_addLine(this, p);
      free(env);
   }
   else {
      InfoScreen_addLine(this, "Could not read process environment.");
   }

   Vector_insertionSort(this->lines);
   Vector_insertionSort(panel->items);
   Panel_setSelected(panel, idx);
}