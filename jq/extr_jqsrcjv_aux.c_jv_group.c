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
struct sort_entry {int /*<<< orphan*/  object; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (struct sort_entry*) ; 
 struct sort_entry* sort_items (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

jv jv_group(jv objects, jv keys) {
  assert(jv_get_kind(objects) == JV_KIND_ARRAY);
  assert(jv_get_kind(keys) == JV_KIND_ARRAY);
  assert(jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys)));
  int n = jv_array_length(jv_copy(objects));
  struct sort_entry* entries = sort_items(objects, keys);
  jv ret = jv_array();
  if (n > 0) {
    jv curr_key = entries[0].key;
    jv group = jv_array_append(jv_array(), entries[0].object);
    for (int i = 1; i < n; i++) {
      if (jv_equal(jv_copy(curr_key), jv_copy(entries[i].key))) {
        jv_free(entries[i].key);
      } else {
        jv_free(curr_key);
        curr_key = entries[i].key;
        ret = jv_array_append(ret, group);
        group = jv_array();
      }
      group = jv_array_append(group, entries[i].object);
    }
    jv_free(curr_key);
    ret = jv_array_append(ret, group);
  }
  jv_mem_free(entries);
  return ret;
}