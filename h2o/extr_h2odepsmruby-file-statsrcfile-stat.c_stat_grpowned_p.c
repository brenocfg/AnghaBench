#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_2__ {int /*<<< orphan*/  st_gid; } ;

/* Variables and functions */
 TYPE_1__* get_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 scalar_t__ mrb_group_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
stat_grpowned_p(mrb_state *mrb, mrb_value self)
{
#ifndef _WIN32
  if (mrb_group_member(mrb, get_stat(mrb, self)->st_gid)) return mrb_true_value();
#endif
  return mrb_false_value();
}