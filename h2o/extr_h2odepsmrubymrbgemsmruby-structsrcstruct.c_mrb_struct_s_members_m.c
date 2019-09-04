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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_s_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_struct_s_members_m(mrb_state *mrb, mrb_value klass)
{
  mrb_value members, ary;

  members = struct_s_members(mrb, mrb_class_ptr(klass));
  ary = mrb_ary_new_capa(mrb, RARRAY_LEN(members));
  mrb_ary_replace(mrb, ary, members);
  return ary;
}