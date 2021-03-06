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
struct TYPE_3__ {scalar_t__ selected; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Panel ;

/* Variables and functions */
 int /*<<< orphan*/  Vector_moveDown (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Vector_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void Panel_moveSelectedDown(Panel* this) {
   assert (this != NULL);

   Vector_moveDown(this->items, this->selected);
   if (this->selected + 1 < Vector_size(this->items))
      this->selected++;
}