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
struct object_slot {int /*<<< orphan*/  value; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_NULL ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 
 int jvp_object_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jvp_object_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jvp_object_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jvp_object_equal(jv o1, jv o2) {
  int len2 = jvp_object_length(o2);
  int len1 = 0;
  for (int i=0; i<jvp_object_size(o1); i++) {
    struct object_slot* slot = jvp_object_get_slot(o1, i);
    if (jv_get_kind(slot->string) == JV_KIND_NULL) continue;
    jv* slot2 = jvp_object_read(o2, slot->string);
    if (!slot2) return 0;
    // FIXME: do less refcounting here
    if (!jv_equal(jv_copy(slot->value), jv_copy(*slot2))) return 0;
    len1++;
  }
  return len1 == len2;
}