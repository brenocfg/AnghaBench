#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  errmsg; } ;
typedef  TYPE_2__ jvp_invalid ;
struct TYPE_11__ {scalar_t__ ptr; } ;
struct TYPE_13__ {TYPE_1__ u; } ;
typedef  TYPE_3__ jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_FLAGS_INVALID_MSG ; 
 scalar_t__ JVP_HAS_FLAGS (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JVP_HAS_KIND (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (TYPE_3__) ; 
 TYPE_3__ jv_null () ; 

jv jv_invalid_get_msg(jv inv) {
  assert(JVP_HAS_KIND(inv, JV_KIND_INVALID));

  jv x;
  if (JVP_HAS_FLAGS(inv, JVP_FLAGS_INVALID_MSG)) {
    x = jv_copy(((jvp_invalid*)inv.u.ptr)->errmsg);
  }
  else {
    x = jv_null();
  }

  jv_free(inv);
  return x;
}