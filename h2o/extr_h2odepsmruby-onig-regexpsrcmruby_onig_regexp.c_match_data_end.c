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
typedef  size_t mrb_int ;
struct TYPE_3__ {int /*<<< orphan*/ * end; } ;
typedef  TYPE_1__ OnigRegion ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t match_data_actual_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_data_check_index (size_t const) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_onig_region_type ; 

__attribute__((used)) static mrb_value
match_data_end(mrb_state* mrb, mrb_value self) {
  mrb_value idx_value;
  mrb_get_args(mrb, "o", &idx_value);
  OnigRegion* reg;
  Data_Get_Struct(mrb, self, &mrb_onig_region_type, reg);
  mrb_int const idx = match_data_actual_index(mrb, self, idx_value);
  match_data_check_index(idx);
  return mrb_fixnum_value(reg->end[idx]);
}