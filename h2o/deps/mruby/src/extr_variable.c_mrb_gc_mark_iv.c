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
struct RObject {int /*<<< orphan*/  iv; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mark_tbl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrb_gc_mark_iv(mrb_state *mrb, struct RObject *obj)
{
  mark_tbl(mrb, obj->iv);
}