#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_8__ {scalar_t__ kind_flags; scalar_t__ offset; scalar_t__ size; TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;

/* Variables and functions */
 scalar_t__ JVP_IS_ALLOCATED (TYPE_2__) ; 
 int /*<<< orphan*/  jv_free (TYPE_2__) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 

int jv_identical(jv a, jv b) {
  int r;
  if (a.kind_flags != b.kind_flags
      || a.offset != b.offset
      || a.size != b.size) {
    r = 0;
  } else {
    if (JVP_IS_ALLOCATED(a) /* b has the same flags */) {
      r = a.u.ptr == b.u.ptr;
    } else {
      r = memcmp(&a.u.ptr, &b.u.ptr, sizeof(a.u)) == 0;
    }
  }
  jv_free(a);
  jv_free(b);
  return r;
}