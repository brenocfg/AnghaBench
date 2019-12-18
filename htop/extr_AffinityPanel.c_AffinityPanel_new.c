#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int used; int* cpus; } ;
struct TYPE_5__ {int cpuCount; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ ProcessList ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_2__ Affinity ;

/* Variables and functions */
 int /*<<< orphan*/  AffinityPanel ; 
 int /*<<< orphan*/  CheckItem ; 
 scalar_t__ CheckItem_newByVal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionBar_newEnterEsc (char*,char*) ; 
 int /*<<< orphan*/  Object_setClass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Panel_new (int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_setHeader (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Settings_cpuId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xStrdup (char*) ; 

Panel* AffinityPanel_new(ProcessList* pl, Affinity* affinity) {
   Panel* this = Panel_new(1, 1, 1, 1, true, Class(CheckItem), FunctionBar_newEnterEsc("Set    ", "Cancel "));
   Object_setClass(this, Class(AffinityPanel));

   Panel_setHeader(this, "Use CPUs:");
   int curCpu = 0;
   for (int i = 0; i < pl->cpuCount; i++) {
      char number[10];
      xSnprintf(number, 9, "%d", Settings_cpuId(pl->settings, i));
      bool mode;
      if (curCpu < affinity->used && affinity->cpus[curCpu] == i) {
         mode = true;
         curCpu++;
      } else {
         mode = false;
      }
      Panel_add(this, (Object*) CheckItem_newByVal(xStrdup(number), mode));
   }
   return this;
}