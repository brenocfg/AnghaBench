#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ htable ;

/* Variables and functions */
 TYPE_1__* RHASH_TBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_kdict_i ; 
 int /*<<< orphan*/  ht_foreach (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
mrb_hash_check_kdict(mrb_state *mrb, mrb_value self)
{
  htable *t;

  t = RHASH_TBL(self);
  if (!t || t->size == 0) return;
  ht_foreach(mrb, t, check_kdict_i, NULL);
}