#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_slot {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;
struct TYPE_2__ {struct object_slot* elements; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* jvp_object_ptr (int /*<<< orphan*/ ) ; 
 int jvp_object_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct object_slot* jvp_object_get_slot(jv object, int slot) {
  assert(slot == -1 || (slot >= 0 && slot < jvp_object_size(object)));
  if (slot == -1) return 0;
  else return &jvp_object_ptr(object)->elements[slot];
}