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
struct TYPE_3__ {int num_regs; scalar_t__* beg; scalar_t__* end; } ;
typedef  TYPE_1__ OnigRegion ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ONIG_REGION_NOTPOS ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_onig_region_type ; 
 int /*<<< orphan*/  str_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mrb_value
match_data_to_a(mrb_state* mrb, mrb_value self) {
  mrb_value cache = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "cache"));
  if(!mrb_nil_p(cache)) {
    return cache;
  }

  mrb_value str = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "string"));
  OnigRegion* reg;
  Data_Get_Struct(mrb, self, &mrb_onig_region_type, reg);

  mrb_value ret = mrb_ary_new_capa(mrb, reg->num_regs);
  int i, ai = mrb_gc_arena_save(mrb);
  for(i = 0; i < reg->num_regs; ++i) {
    if(reg->beg[i] == ONIG_REGION_NOTPOS) {
      mrb_ary_push(mrb, ret, mrb_nil_value());
    } else {
      mrb_ary_push(mrb, ret, str_substr(mrb, str, reg->beg[i], reg->end[i] - reg->beg[i]));
    }
    mrb_gc_arena_restore(mrb, ai);
  }
  return ret;
}