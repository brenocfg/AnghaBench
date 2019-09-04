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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array_get (int /*<<< orphan*/ ,int) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array_slice (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_dels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jv_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv delpaths_sorted(jv object, jv paths, int start) {
  jv delkeys = jv_array();
  for (int i=0; i<jv_array_length(jv_copy(paths));) {
    int j = i;
    assert(jv_array_length(jv_array_get(jv_copy(paths), i)) > start);
    int delkey = jv_array_length(jv_array_get(jv_copy(paths), i)) == start + 1;
    jv key = jv_array_get(jv_array_get(jv_copy(paths), i), start);
    while (j < jv_array_length(jv_copy(paths)) &&
           jv_equal(jv_copy(key), jv_array_get(jv_array_get(jv_copy(paths), j), start)))
      j++;
    // if i <= entry < j, then entry starts with key
    if (delkey) {
      // deleting this entire key, we don't care about any more specific deletions
      delkeys = jv_array_append(delkeys, key);
    } else {
      // deleting certain sub-parts of this key
      jv subobject = jv_get(jv_copy(object), jv_copy(key));
      if (!jv_is_valid(subobject)) {
        jv_free(key);
        jv_free(object);
        object = subobject;
        break;
      } else if (jv_get_kind(subobject) == JV_KIND_NULL) {
        jv_free(key);
        jv_free(subobject);
      } else {
        jv newsubobject = delpaths_sorted(subobject, jv_array_slice(jv_copy(paths), i, j), start+1);
        if (!jv_is_valid(newsubobject)) {
          jv_free(key);
          jv_free(object);
          object = newsubobject;
          break;
        }
        object = jv_set(object, key, newsubobject);
      }
      if (!jv_is_valid(object)) break;
    }
    i = j;
  }
  jv_free(paths);
  if (jv_is_valid(object))
    object = jv_dels(object, delkeys);
  else
    jv_free(delkeys);
  return object;
}