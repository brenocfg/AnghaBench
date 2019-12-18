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
struct object_slot {scalar_t__ hash; int next; int /*<<< orphan*/  value; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  JV_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int* jvp_object_find_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 
 struct object_slot* jvp_object_next_slot (int /*<<< orphan*/ ,struct object_slot*) ; 
 int /*<<< orphan*/  jvp_object_unshare (int /*<<< orphan*/ ) ; 
 scalar_t__ jvp_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jvp_string_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jvp_object_delete(jv* object, jv key) {
  assert(JVP_HAS_KIND(key, JV_KIND_STRING));
  *object = jvp_object_unshare(*object);
  int* bucket = jvp_object_find_bucket(*object, key);
  int* prev_ptr = bucket;
  uint32_t hash = jvp_string_hash(key);
  for (struct object_slot* curr = jvp_object_get_slot(*object, *bucket);
       curr;
       curr = jvp_object_next_slot(*object, curr)) {
    if (hash == curr->hash && jvp_string_equal(key, curr->string)) {
      *prev_ptr = curr->next;
      jvp_string_free(curr->string);
      curr->string = JV_NULL;
      jv_free(curr->value);
      return 1;
    }
    prev_ptr = &curr->next;
  }
  return 0;
}