#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct object_slot {int /*<<< orphan*/  value; int /*<<< orphan*/  string; } ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_HAS_KIND (TYPE_2__,int /*<<< orphan*/ ) ; 
 scalar_t__ JV_KIND_NULL ; 
 int /*<<< orphan*/  JV_KIND_OBJECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (int /*<<< orphan*/ ) ; 
 struct object_slot* jvp_object_get_slot (TYPE_2__,int) ; 
 int /*<<< orphan*/  jvp_object_ptr (TYPE_2__) ; 
 int jvp_object_size (TYPE_2__) ; 
 scalar_t__ jvp_refcnt_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jvp_object_free(jv o) {
  assert(JVP_HAS_KIND(o, JV_KIND_OBJECT));
  if (jvp_refcnt_dec(o.u.ptr)) {
    for (int i=0; i<jvp_object_size(o); i++) {
      struct object_slot* slot = jvp_object_get_slot(o, i);
      if (jv_get_kind(slot->string) != JV_KIND_NULL) {
        jvp_string_free(slot->string);
        jv_free(slot->value);
      }
    }
    jv_mem_free(jvp_object_ptr(o));
  }
}