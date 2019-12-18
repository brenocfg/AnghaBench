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
struct os_each_object_data {int /*<<< orphan*/  count; int /*<<< orphan*/  block; scalar_t__ target_module; } ;
struct RBasic {int tt; int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int MRB_EACH_OBJ_OK ; 
#define  MRB_TT_ENV 129 
#define  MRB_TT_ICLASS 128 
 int /*<<< orphan*/  mrb_obj_is_kind_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RBasic*) ; 
 scalar_t__ mrb_object_dead_p (int /*<<< orphan*/ *,struct RBasic*) ; 
 int /*<<< orphan*/  mrb_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
os_each_object_cb(mrb_state *mrb, struct RBasic *obj, void *ud)
{
  struct os_each_object_data *d = (struct os_each_object_data*)ud;

  /* filter dead objects */
  if (mrb_object_dead_p(mrb, obj)) {
    return MRB_EACH_OBJ_OK;
  }

  /* filter internal objects */
  switch (obj->tt) {
  case MRB_TT_ENV:
  case MRB_TT_ICLASS:
    return MRB_EACH_OBJ_OK;
  default:
    break;
  }

  /* filter half baked (or internal) objects */
  if (!obj->c) return MRB_EACH_OBJ_OK;

  /* filter class kind if target module defined */
  if (d->target_module && !mrb_obj_is_kind_of(mrb, mrb_obj_value(obj), d->target_module)) {
    return MRB_EACH_OBJ_OK;
  }

  mrb_yield(mrb, d->block, mrb_obj_value(obj));
  ++d->count;
  return MRB_EACH_OBJ_OK;
}