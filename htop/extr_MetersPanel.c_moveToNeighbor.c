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
struct TYPE_5__ {int /*<<< orphan*/  super; int /*<<< orphan*/  meters; scalar_t__ moving; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ MetersPanel ;
typedef  int /*<<< orphan*/  Meter ;

/* Variables and functions */
 scalar_t__ Meter_toListItem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MetersPanel_setMoving (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Panel_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Panel_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Vector_insert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int Vector_size (int /*<<< orphan*/ ) ; 
 scalar_t__ Vector_take (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool moveToNeighbor(MetersPanel* this, MetersPanel* neighbor, int selected) {
   Panel* super = (Panel*) this;
   if (this->moving) {
      if (neighbor) {
         if (selected < Vector_size(this->meters)) {
            MetersPanel_setMoving(this, false);

            Meter* meter = (Meter*) Vector_take(this->meters, selected);
            Panel_remove(super, selected);
            Vector_insert(neighbor->meters, selected, meter);
            Panel_insert(&(neighbor->super), selected, (Object*) Meter_toListItem(meter, false));
            Panel_setSelected(&(neighbor->super), selected);

            MetersPanel_setMoving(neighbor, true);
            return true;
         }
      }
   }
   return false;
}