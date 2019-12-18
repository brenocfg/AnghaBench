#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ h; int /*<<< orphan*/  (* draw ) (TYPE_3__*,int,int,int) ;TYPE_2__* pl; scalar_t__ drawData; } ;
struct TYPE_9__ {TYPE_1__* settings; } ;
struct TYPE_8__ {scalar_t__ headerMargin; } ;
typedef  TYPE_3__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  AllCPUsMeter_getRange (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static void DualColCPUsMeter_draw(Meter* this, int x, int y, int w) {
   Meter** meters = (Meter**) this->drawData;
   int start, count;
   int pad = this->pl->settings->headerMargin ? 2 : 0;
   AllCPUsMeter_getRange(this, &start, &count);
   int height = (count+1)/2;
   int startY = y;
   for (int i = 0; i < height; i++) {
      meters[i]->draw(meters[i], x, y, (w-pad)/2);
      y += meters[i]->h;
   }
   y = startY;
   for (int i = height; i < count; i++) {
      meters[i]->draw(meters[i], x+(w-1)/2+1+(pad/2), y, (w-pad)/2);
      y += meters[i]->h;
   }
}