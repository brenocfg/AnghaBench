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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_gc_state ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ mrb_gc ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  incremental_gc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
incremental_gc_until(mrb_state *mrb, mrb_gc *gc, mrb_gc_state to_state)
{
  do {
    incremental_gc(mrb, gc, SIZE_MAX);
  } while (gc->state != to_state);
}