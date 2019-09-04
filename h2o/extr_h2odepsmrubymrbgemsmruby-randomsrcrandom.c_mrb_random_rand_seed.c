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
struct TYPE_4__ {int /*<<< orphan*/  has_seed; } ;
typedef  TYPE_1__ mt_state ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_random_mt_srand (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mrb_random_rand_seed(mrb_state *mrb, mt_state *t)
{
  if (!t->has_seed) {
    mrb_random_mt_srand(mrb, t, mrb_nil_value());
  }
}