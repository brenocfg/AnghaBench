#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ptr; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 scalar_t__ JV_KIND_INVALID ; 
 scalar_t__ JV_KIND_OBJECT ; 
 scalar_t__ JV_KIND_STRING ; 
 scalar_t__ jv_get_kind (TYPE_2__) ; 
 int /*<<< orphan*/  jvp_refcnt_inc (scalar_t__) ; 

jv jv_copy(jv j) {
  if (jv_get_kind(j) == JV_KIND_ARRAY ||
      jv_get_kind(j) == JV_KIND_STRING ||
      jv_get_kind(j) == JV_KIND_OBJECT ||
      (jv_get_kind(j) == JV_KIND_INVALID && j.u.ptr != 0)) {
    jvp_refcnt_inc(j.u.ptr);
  }
  return j;
}