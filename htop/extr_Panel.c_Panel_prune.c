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
struct TYPE_3__ {int needsRedraw; scalar_t__ oldSelected; scalar_t__ selected; scalar_t__ scrollV; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Panel ;

/* Variables and functions */
 int /*<<< orphan*/  Vector_prune (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void Panel_prune(Panel* this) {
   assert (this != NULL);

   Vector_prune(this->items);
   this->scrollV = 0;
   this->selected = 0;
   this->oldSelected = 0;
   this->needsRedraw = true;
}