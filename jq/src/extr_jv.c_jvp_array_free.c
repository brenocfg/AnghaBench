#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int length; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_2__ jvp_array ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
typedef  TYPE_3__ jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_HAS_KIND (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (TYPE_2__*) ; 
 TYPE_2__* jvp_array_ptr (TYPE_3__) ; 
 scalar_t__ jvp_refcnt_dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jvp_array_free(jv a) {
  assert(JVP_HAS_KIND(a, JV_KIND_ARRAY));
  if (jvp_refcnt_dec(a.u.ptr)) {
    jvp_array* array = jvp_array_ptr(a);
    for (int i=0; i<array->length; i++) {
      jv_free(array->elements[i]);
    }
    jv_mem_free(array);
  }
}