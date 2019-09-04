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

/* Variables and functions */
 int /*<<< orphan*/  mrb_gc_mark_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hash_mark_i(mrb_state *mrb, mrb_value key, mrb_value val, void *p)
{
  mrb_gc_mark_value(mrb, key);
  mrb_gc_mark_value(mrb, val);
  return 0;
}