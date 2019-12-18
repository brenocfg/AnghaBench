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
struct TYPE_9__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_11__ {TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  refcnt; TYPE_3__ errmsg; } ;
typedef  TYPE_2__ jvp_invalid ;
typedef  TYPE_3__ jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_FLAGS_INVALID_MSG ; 
 scalar_t__ JVP_HAS_KIND (TYPE_3__,int /*<<< orphan*/ ) ; 
 TYPE_3__ JV_INVALID ; 
 int /*<<< orphan*/  JV_KIND_NULL ; 
 int /*<<< orphan*/  JV_REFCNT_INIT ; 
 TYPE_2__* jv_mem_alloc (int) ; 

jv jv_invalid_with_msg(jv err) {
  if (JVP_HAS_KIND(err, JV_KIND_NULL))
    return JV_INVALID;
  jvp_invalid* i = jv_mem_alloc(sizeof(jvp_invalid));
  i->refcnt = JV_REFCNT_INIT;
  i->errmsg = err;

  jv x = {JVP_FLAGS_INVALID_MSG, 0, 0, 0, {&i->refcnt}};
  return x;
}