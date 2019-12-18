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
struct RArray {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ ARY_LEN (struct RArray*) ; 
 int /*<<< orphan*/ * ARY_PTR (struct RArray*) ; 
 int /*<<< orphan*/  ARY_SET_LEN (struct RArray*,scalar_t__) ; 
 struct RArray* ary_new_capa (int /*<<< orphan*/ *,scalar_t__) ; 
 struct RArray* mrb_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RArray*) ; 

__attribute__((used)) static mrb_value
mrb_ary_reverse(mrb_state *mrb, mrb_value self)
{
  struct RArray *a = mrb_ary_ptr(self), *b = ary_new_capa(mrb, ARY_LEN(a));
  mrb_int len = ARY_LEN(a);

  if (len > 0) {
    mrb_value *p1, *p2, *e;

    p1 = ARY_PTR(a);
    e  = p1 + len;
    p2 = ARY_PTR(b) + len - 1;
    while (p1 < e) {
      *p2-- = *p1++;
    }
    ARY_SET_LEN(b, len);
  }
  return mrb_obj_value(b);
}