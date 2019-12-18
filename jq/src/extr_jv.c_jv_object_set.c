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
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_OBJECT ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jvp_object_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

jv jv_object_set(jv object, jv key, jv value) {
  assert(JVP_HAS_KIND(object, JV_KIND_OBJECT));
  assert(JVP_HAS_KIND(key, JV_KIND_STRING));
  // copy/free of object, key, value coalesced
  jv* slot = jvp_object_write(&object, key);
  jv_free(*slot);
  *slot = value;
  return object;
}