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
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 size_t RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RSTRUCT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_name_error (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_struct_modify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sym2str (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mrb_symbol (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  struct_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_struct_aset_sym(mrb_state *mrb, mrb_value s, mrb_sym id, mrb_value val)
{
  mrb_value members, *ptr;
  const mrb_value *ptr_members;
  mrb_int i, len;

  members = struct_members(mrb, s);
  len = RARRAY_LEN(members);
  ptr = RSTRUCT_PTR(s);
  ptr_members = RARRAY_PTR(members);
  for (i=0; i<len; i++) {
    if (mrb_symbol(ptr_members[i]) == id) {
      mrb_struct_modify(mrb, s);
      ptr[i] = val;
      return val;
    }
  }
  mrb_name_error(mrb, id, "no member '%S' in struct", mrb_sym2str(mrb, id));
  return val;                   /* not reach */
}