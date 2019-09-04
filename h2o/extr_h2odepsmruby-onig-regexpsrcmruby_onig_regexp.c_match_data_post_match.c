#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {scalar_t__* end; } ;
typedef  TYPE_1__ OnigRegion ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_onig_region_type ; 
 int /*<<< orphan*/  str_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mrb_value
match_data_post_match(mrb_state* mrb, mrb_value self) {
  OnigRegion* reg;
  Data_Get_Struct(mrb, self, &mrb_onig_region_type, reg);
  mrb_value str = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "string"));
  return str_substr(mrb, str, reg->end[0], RSTRING_LEN(str) - reg->end[0]);
}