#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ h; int /*<<< orphan*/  (* draw ) (TYPE_1__*,int,int,int) ;scalar_t__ drawData; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  AllCPUsMeter_getRange (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void SingleColCPUsMeter_draw(Meter* this, int x, int y, int w) {
   Meter** meters = (Meter**) this->drawData;
   int start, count;
   AllCPUsMeter_getRange(this, &start, &count);
   for (int i = 0; i < count; i++) {
      meters[i]->draw(meters[i], x, y, w);
      y += meters[i]->h;
   }
}