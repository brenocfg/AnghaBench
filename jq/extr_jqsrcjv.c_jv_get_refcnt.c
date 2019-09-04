#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ptr; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_3__ jv ;
struct TYPE_6__ {int count; } ;

/* Variables and functions */
#define  JV_KIND_ARRAY 130 
#define  JV_KIND_OBJECT 129 
#define  JV_KIND_STRING 128 
 int jv_get_kind (TYPE_3__) ; 

int jv_get_refcnt(jv j) {
  switch (jv_get_kind(j)) {
  case JV_KIND_ARRAY:
  case JV_KIND_STRING:
  case JV_KIND_OBJECT:
    return j.u.ptr->count;
  default:
    return 1;
  }
}