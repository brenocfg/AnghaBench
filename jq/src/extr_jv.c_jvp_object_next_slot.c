#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct object_slot {int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct object_slot* jvp_object_next_slot(jv object, struct object_slot* slot) {
  return jvp_object_get_slot(object, slot->next);
}