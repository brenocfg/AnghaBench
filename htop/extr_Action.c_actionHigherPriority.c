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
struct TYPE_3__ {scalar_t__ panel; } ;
typedef  TYPE_1__ State ;
typedef  int /*<<< orphan*/  MainPanel ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  HTOP_OK ; 
 int /*<<< orphan*/  HTOP_REFRESH ; 
 int changePriority (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Htop_Reaction actionHigherPriority(State* st) {
   bool changed = changePriority((MainPanel*)st->panel, -1);
   return changed ? HTOP_REFRESH : HTOP_OK;
}