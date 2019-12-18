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
typedef  int /*<<< orphan*/  const mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/ * DATA_TYPE (int /*<<< orphan*/  const) ; 
 scalar_t__ MRB_TT_DATA ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_data_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_onig_region_type ; 
 int /*<<< orphan*/  const mrb_str_dup (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int mrb_string_p (int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_type (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  onig_region_new () ; 

__attribute__((used)) static mrb_value
create_onig_region(mrb_state* mrb, mrb_value const str, mrb_value rex) {
  mrb_assert(mrb_string_p(str));
  mrb_assert(mrb_type(rex) == MRB_TT_DATA && DATA_TYPE(rex) == &mrb_onig_regexp_type);
  mrb_value const c = mrb_obj_value(mrb_data_object_alloc(
      mrb, mrb_class_get(mrb, "OnigMatchData"), onig_region_new(), &mrb_onig_region_type));
  mrb_iv_set(mrb, c, mrb_intern_lit(mrb, "string"), mrb_str_dup(mrb, str));
  mrb_iv_set(mrb, c, mrb_intern_lit(mrb, "regexp"), rex);
  return c;
}