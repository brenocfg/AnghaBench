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
struct object_slot {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int ITER_FINISHED ; 
 int JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ JV_KIND_NULL ; 
 int /*<<< orphan*/  JV_KIND_OBJECT ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 
 int jvp_object_size (int /*<<< orphan*/ ) ; 

int jv_object_iter_next(jv object, int iter) {
  assert(JVP_HAS_KIND(object, JV_KIND_OBJECT));
  assert(iter != ITER_FINISHED);
  struct object_slot* slot;
  do {
    iter++;
    if (iter >= jvp_object_size(object))
      return ITER_FINISHED;
    slot = jvp_object_get_slot(object, iter);
  } while (jv_get_kind(slot->string) == JV_KIND_NULL);
  assert(jv_get_kind(jvp_object_get_slot(object,iter)->string)
         == JV_KIND_STRING);
  return iter;
}