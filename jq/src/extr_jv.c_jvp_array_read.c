#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ jvp_array ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int jvp_array_length (int /*<<< orphan*/ ) ; 
 int jvp_array_offset (int /*<<< orphan*/ ) ; 
 TYPE_1__* jvp_array_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv* jvp_array_read(jv a, int i) {
  assert(JVP_HAS_KIND(a, JV_KIND_ARRAY));
  if (i >= 0 && i < jvp_array_length(a)) {
    jvp_array* array = jvp_array_ptr(a);
    assert(i + jvp_array_offset(a) < array->length);
    return &array->elements[i + jvp_array_offset(a)];
  } else {
    return 0;
  }
}