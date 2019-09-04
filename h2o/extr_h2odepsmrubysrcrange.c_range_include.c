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
struct RRange {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE_BEG (struct RRange*) ; 
 int /*<<< orphan*/  RANGE_END (struct RRange*) ; 
 scalar_t__ RANGE_EXCL (struct RRange*) ; 
 int /*<<< orphan*/  mrb_bool_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct RRange* mrb_range_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ r_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_gt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
range_include(mrb_state *mrb, mrb_value range)
{
  mrb_value val;
  struct RRange *r = mrb_range_ptr(mrb, range);
  mrb_value beg, end;
  mrb_bool include_p;

  mrb_get_args(mrb, "o", &val);

  beg = RANGE_BEG(r);
  end = RANGE_END(r);
  include_p = r_le(mrb, beg, val) &&                 /* beg <= val */
              (RANGE_EXCL(r) ? r_gt(mrb, end, val)   /* end >  val */
                             : r_ge(mrb, end, val)); /* end >= val */

  return mrb_bool_value(include_p);
}