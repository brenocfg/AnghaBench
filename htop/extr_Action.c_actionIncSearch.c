#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inc; } ;
struct TYPE_4__ {scalar_t__ panel; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ MainPanel ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int HTOP_KEEP_FOLLOWING ; 
 int HTOP_REFRESH ; 
 int /*<<< orphan*/  INC_SEARCH ; 
 int /*<<< orphan*/  IncSet_activate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static Htop_Reaction actionIncSearch(State* st) {
   IncSet_activate(((MainPanel*)st->panel)->inc, INC_SEARCH, st->panel);
   return HTOP_REFRESH | HTOP_KEEP_FOLLOWING;
}