#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ ptr; } ;
struct TYPE_15__ {scalar_t__ kind_flags; scalar_t__ size; TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;

/* Variables and functions */
#define  JV_KIND_ARRAY 130 
 int JV_KIND_NUMBER ; 
#define  JV_KIND_OBJECT 129 
#define  JV_KIND_STRING 128 
 int /*<<< orphan*/  jv_free (TYPE_2__) ; 
 int jv_get_kind (TYPE_2__) ; 
 scalar_t__ jv_number_value (TYPE_2__) ; 
 int jvp_array_equal (TYPE_2__,TYPE_2__) ; 
 int jvp_object_equal (TYPE_2__,TYPE_2__) ; 
 int jvp_string_equal (TYPE_2__,TYPE_2__) ; 

int jv_equal(jv a, jv b) {
  int r;
  if (jv_get_kind(a) != jv_get_kind(b)) {
    r = 0;
  } else if (jv_get_kind(a) == JV_KIND_NUMBER) {
    r = jv_number_value(a) == jv_number_value(b);
  } else if (a.kind_flags == b.kind_flags &&
             a.size == b.size &&
             a.u.ptr == b.u.ptr) {
    r = 1;
  } else {
    switch (jv_get_kind(a)) {
    case JV_KIND_ARRAY:
      r = jvp_array_equal(a, b);
      break;
    case JV_KIND_STRING:
      r = jvp_string_equal(a, b);
      break;
    case JV_KIND_OBJECT:
      r = jvp_object_equal(a, b);
      break;
    default:
      r = 1;
      break;
    }
  }
  jv_free(a);
  jv_free(b);
  return r;
}