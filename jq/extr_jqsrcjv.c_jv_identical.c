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
struct TYPE_7__ {int /*<<< orphan*/  number; int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {scalar_t__ kind_flags; scalar_t__ offset; scalar_t__ size; TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;

/* Variables and functions */
#define  JV_KIND_ARRAY 131 
#define  JV_KIND_NUMBER 130 
#define  JV_KIND_OBJECT 129 
#define  JV_KIND_STRING 128 
 int /*<<< orphan*/  jv_free (TYPE_2__) ; 
 int jv_get_kind (TYPE_2__) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int jv_identical(jv a, jv b) {
  int r;
  if (a.kind_flags != b.kind_flags
      || a.offset != b.offset
      || a.size != b.size) {
    r = 0;
  } else {
    switch (jv_get_kind(a)) {
    case JV_KIND_ARRAY:
    case JV_KIND_STRING:
    case JV_KIND_OBJECT:
      r = a.u.ptr == b.u.ptr;
      break;
    case JV_KIND_NUMBER:
      r = memcmp(&a.u.number, &b.u.number, sizeof(a.u.number)) == 0;
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