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
struct TYPE_5__ {int tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  panel; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Process ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  HTOP_REFRESH ; 
 scalar_t__ Panel_get (int /*<<< orphan*/ ,int) ; 
 int Panel_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Htop_Reaction actionUntagAll(State* st) {
   for (int i = 0; i < Panel_size(st->panel); i++) {
      Process* p = (Process*) Panel_get(st->panel, i);
      p->tag = false;
   }
   return HTOP_REFRESH;
}