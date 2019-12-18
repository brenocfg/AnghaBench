#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct object_slot {void* value; void* string; } ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;
struct TYPE_15__ {int /*<<< orphan*/  next_free; } ;

/* Variables and functions */
 scalar_t__ JVP_HAS_KIND (TYPE_2__,int /*<<< orphan*/ ) ; 
 scalar_t__ JV_KIND_NULL ; 
 int /*<<< orphan*/  JV_KIND_OBJECT ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 void* jv_copy (void*) ; 
 scalar_t__ jv_get_kind (void*) ; 
 int* jvp_object_buckets (TYPE_2__) ; 
 int /*<<< orphan*/  jvp_object_free (TYPE_2__) ; 
 struct object_slot* jvp_object_get_slot (TYPE_2__,int) ; 
 TYPE_2__ jvp_object_new (int) ; 
 TYPE_6__* jvp_object_ptr (TYPE_2__) ; 
 int jvp_object_size (TYPE_2__) ; 
 scalar_t__ jvp_refcnt_unshared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static jv jvp_object_unshare(jv object) {
  assert(JVP_HAS_KIND(object, JV_KIND_OBJECT));
  if (jvp_refcnt_unshared(object.u.ptr))
    return object;

  jv new_object = jvp_object_new(jvp_object_size(object));
  jvp_object_ptr(new_object)->next_free = jvp_object_ptr(object)->next_free;
  for (int i=0; i<jvp_object_size(new_object); i++) {
    struct object_slot* old_slot = jvp_object_get_slot(object, i);
    struct object_slot* new_slot = jvp_object_get_slot(new_object, i);
    *new_slot = *old_slot;
    if (jv_get_kind(old_slot->string) != JV_KIND_NULL) {
      new_slot->string = jv_copy(old_slot->string);
      new_slot->value = jv_copy(old_slot->value);
    }
  }

  int* old_buckets = jvp_object_buckets(object);
  int* new_buckets = jvp_object_buckets(new_object);
  memcpy(new_buckets, old_buckets, sizeof(int) * jvp_object_size(new_object)*2);

  jvp_object_free(object);
  assert(jvp_refcnt_unshared(new_object.u.ptr));
  return new_object;
}