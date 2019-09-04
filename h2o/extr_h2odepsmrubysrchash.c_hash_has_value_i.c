#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct has_v_arg {int /*<<< orphan*/  found; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mrb_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hash_has_value_i(mrb_state *mrb, mrb_value key, mrb_value val, void *p)
{
  struct has_v_arg *arg = (struct has_v_arg*)p;
  
  if (mrb_equal(mrb, arg->val, val)) {
    arg->found = TRUE;
    return 1;
  }
  return 0;
}