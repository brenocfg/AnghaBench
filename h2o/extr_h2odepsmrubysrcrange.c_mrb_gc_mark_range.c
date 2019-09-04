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
struct RRange {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE_BEG (struct RRange*) ; 
 int /*<<< orphan*/  RANGE_END (struct RRange*) ; 
 scalar_t__ RANGE_INITIALIZED_P (struct RRange*) ; 
 int /*<<< orphan*/  mrb_gc_mark_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrb_gc_mark_range(mrb_state *mrb, struct RRange *r)
{
  if (RANGE_INITIALIZED_P(r)) {
    mrb_gc_mark_value(mrb, RANGE_BEG(r));
    mrb_gc_mark_value(mrb, RANGE_END(r));
  }
}