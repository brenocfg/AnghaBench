#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * inc; } ;
struct TYPE_6__ {TYPE_1__* pl; scalar_t__ panel; } ;
struct TYPE_5__ {int /*<<< orphan*/  incFilter; } ;
typedef  TYPE_2__ State ;
typedef  TYPE_3__ MainPanel ;
typedef  int /*<<< orphan*/  IncSet ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int HTOP_KEEP_FOLLOWING ; 
 int HTOP_REFRESH ; 
 int /*<<< orphan*/  INC_FILTER ; 
 int /*<<< orphan*/  IncSet_activate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IncSet_filter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Htop_Reaction actionIncFilter(State* st) {
   IncSet* inc = ((MainPanel*)st->panel)->inc;
   IncSet_activate(inc, INC_FILTER, st->panel);
   st->pl->incFilter = IncSet_filter(inc);
   return HTOP_REFRESH | HTOP_KEEP_FOLLOWING;
}