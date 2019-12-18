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
typedef  int /*<<< orphan*/  mrb_debug_context ;

/* Variables and functions */
 int /*<<< orphan*/ * _debug_context ; 
 int /*<<< orphan*/ * mrb_debug_context_new (int /*<<< orphan*/ *) ; 

mrb_debug_context*
mrb_debug_context_get(mrb_state *mrb)
{
  if (!_debug_context) {
    _debug_context = mrb_debug_context_new(mrb);
  }
  return _debug_context;
}