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
struct object_slot {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int* jvp_object_find_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct object_slot* jvp_object_find_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static jv* jvp_object_read(jv object, jv key) {
  assert(JVP_HAS_KIND(key, JV_KIND_STRING));
  int* bucket = jvp_object_find_bucket(object, key);
  struct object_slot* slot = jvp_object_find_slot(object, key, bucket);
  if (slot == 0) return 0;
  else return &slot->value;
}