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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/ * _debug_context ; 
 int /*<<< orphan*/  mrb_debug_delete_break_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
mrb_debug_context_free(mrb_state *mrb)
{
  if (_debug_context) {
    mrb_debug_delete_break_all(mrb, _debug_context);
    mrb_free(mrb, _debug_context);
    _debug_context = NULL;
  }
}