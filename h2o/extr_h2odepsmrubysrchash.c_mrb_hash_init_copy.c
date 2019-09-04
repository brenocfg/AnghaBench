#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct RHash {int /*<<< orphan*/  flags; int /*<<< orphan*/  ht; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_11__ {int /*<<< orphan*/  hash_class; } ;
typedef  TYPE_1__ mrb_state ;
typedef  int /*<<< orphan*/  htable ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  MRB_HASH_DEFAULT ; 
 int /*<<< orphan*/  MRB_HASH_PROC_DEFAULT ; 
 scalar_t__ MRB_RHASH_DEFAULT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MRB_RHASH_PROCDEFAULT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_HASH ; 
 int /*<<< orphan*/  RHASH_IFNONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RHASH_TBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_copy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_iv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_class (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_equal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RHash*) ; 
 int /*<<< orphan*/  mrb_raise (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_hash_init_copy(mrb_state *mrb, mrb_value self)
{
  mrb_value orig;
  struct RHash* copy;
  htable *orig_h;
  mrb_value ifnone, vret;

  mrb_get_args(mrb, "o", &orig);
  if (mrb_obj_equal(mrb, self, orig)) return self;
  if ((mrb_type(self) != mrb_type(orig)) || (mrb_obj_class(mrb, self) != mrb_obj_class(mrb, orig))) {
      mrb_raise(mrb, E_TYPE_ERROR, "initialize_copy should take same class object");
  }

  orig_h = RHASH_TBL(self);
  copy = (struct RHash*)mrb_obj_alloc(mrb, MRB_TT_HASH, mrb->hash_class);
  copy->ht = ht_copy(mrb, orig_h);

  if (MRB_RHASH_DEFAULT_P(self)) {
    copy->flags |= MRB_HASH_DEFAULT;
  }
  if (MRB_RHASH_PROCDEFAULT_P(self)) {
    copy->flags |= MRB_HASH_PROC_DEFAULT;
  }
  vret = mrb_obj_value(copy);
  ifnone = RHASH_IFNONE(self);
  if (!mrb_nil_p(ifnone)) {
      mrb_iv_set(mrb, vret, mrb_intern_lit(mrb, "ifnone"), ifnone);
  }
  return vret;
}