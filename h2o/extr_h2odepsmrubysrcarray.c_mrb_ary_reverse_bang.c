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
typedef  void* mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 int ARY_LEN (struct RArray*) ; 
 void** ARY_PTR (struct RArray*) ; 
 int /*<<< orphan*/  ary_modify (int /*<<< orphan*/ *,struct RArray*) ; 
 struct RArray* mrb_ary_ptr (void*) ; 

__attribute__((used)) static mrb_value
mrb_ary_reverse_bang(mrb_state *mrb, mrb_value self)
{
  struct RArray *a = mrb_ary_ptr(self);
  mrb_int len = ARY_LEN(a);

  if (len > 1) {
    mrb_value *p1, *p2;

    ary_modify(mrb, a);
    p1 = ARY_PTR(a);
    p2 = p1 + len - 1;

    while (p1 < p2) {
      mrb_value tmp = *p1;
      *p1++ = *p2;
      *p2-- = tmp;
    }
  }
  return self;
}