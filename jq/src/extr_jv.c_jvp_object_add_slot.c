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
struct object_slot {int next; int /*<<< orphan*/  string; int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {int next_free; } ;
typedef  TYPE_1__ jvp_object ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* jvp_object_ptr (int /*<<< orphan*/ ) ; 
 int jvp_object_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct object_slot* jvp_object_add_slot(jv object, jv key, int* bucket) {
  jvp_object* o = jvp_object_ptr(object);
  int newslot_idx = o->next_free;
  if (newslot_idx == jvp_object_size(object)) return 0;
  struct object_slot* newslot = jvp_object_get_slot(object, newslot_idx);
  o->next_free++;
  newslot->next = *bucket;
  *bucket = newslot_idx;
  newslot->hash = jvp_string_hash(key);
  newslot->string = key;
  return newslot;
}