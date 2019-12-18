#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  errmsg; } ;
typedef  TYPE_2__ jvp_invalid ;
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_3__ jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_FLAGS_INVALID_MSG ; 
 scalar_t__ JVP_HAS_FLAGS (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JVP_HAS_KIND (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (scalar_t__) ; 
 scalar_t__ jvp_refcnt_dec (scalar_t__) ; 

__attribute__((used)) static void jvp_invalid_free(jv x) {
  assert(JVP_HAS_KIND(x, JV_KIND_INVALID));
  if (JVP_HAS_FLAGS(x, JVP_FLAGS_INVALID_MSG) && jvp_refcnt_dec(x.u.ptr)) {
    jv_free(((jvp_invalid*)x.u.ptr)->errmsg);
    jv_mem_free(x.u.ptr);
  }
}