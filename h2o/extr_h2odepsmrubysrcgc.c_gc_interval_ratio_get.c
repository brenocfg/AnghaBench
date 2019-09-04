#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_4__ {int /*<<< orphan*/  interval_ratio; } ;
struct TYPE_5__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
gc_interval_ratio_get(mrb_state *mrb, mrb_value obj)
{
  return mrb_fixnum_value(mrb->gc.interval_ratio);
}