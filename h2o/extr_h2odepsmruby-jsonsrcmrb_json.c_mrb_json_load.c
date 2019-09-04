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
typedef  int /*<<< orphan*/  JSON_Value ;

/* Variables and functions */
 int /*<<< orphan*/  E_PARSER_ERROR ; 
 int /*<<< orphan*/ * json_parse_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_value_to_mrb_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_yield_argv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
mrb_json_load(mrb_state *mrb, mrb_value self)
{
  mrb_value value, blk;
  JSON_Value *root_value;
  mrb_value json = mrb_nil_value();
  mrb_get_args(mrb, "S&", &json, &blk);

  root_value = json_parse_string(mrb_str_to_cstr(mrb, json));
  if (!root_value) {
    mrb_raise(mrb, E_PARSER_ERROR, "invalid json");
  }

  value = json_value_to_mrb_value(mrb, root_value);
  json_value_free(root_value);
  if (!mrb_nil_p(blk)) {
    mrb_value args[1];
    args[0] = value;
    mrb_yield_argv(mrb, blk, 1, args);
  }
  return value;
}