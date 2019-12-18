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
typedef  scalar_t__ uint32_t ;
struct object_slot {scalar_t__ hash; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 
 struct object_slot* jvp_object_next_slot (int /*<<< orphan*/ ,struct object_slot*) ; 
 scalar_t__ jvp_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jvp_string_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct object_slot* jvp_object_find_slot(jv object, jv keystr, int* bucket) {
  uint32_t hash = jvp_string_hash(keystr);
  for (struct object_slot* curr = jvp_object_get_slot(object, *bucket);
       curr;
       curr = jvp_object_next_slot(object, curr)) {
    if (curr->hash == hash && jvp_string_equal(keystr, curr->string)) {
      return curr;
    }
  }
  return 0;
}