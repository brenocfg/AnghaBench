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
struct TYPE_4__ {TYPE_2__* dts_buffer; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_5__ {int /*<<< orphan*/  dtb_flags; int /*<<< orphan*/ * dtb_tomax; } ;
typedef  TYPE_2__ dtrace_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEBUF_INACTIVE ; 
 size_t curcpu ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_buffer_activate(dtrace_state_t *state)
{
	dtrace_buffer_t *buf;
	dtrace_icookie_t cookie = dtrace_interrupt_disable();

	buf = &state->dts_buffer[curcpu];

	if (buf->dtb_tomax != NULL) {
		/*
		 * We might like to assert that the buffer is marked inactive,
		 * but this isn't necessarily true:  the buffer for the CPU
		 * that processes the BEGIN probe has its buffer activated
		 * manually.  In this case, we take the (harmless) action
		 * re-clearing the bit INACTIVE bit.
		 */
		buf->dtb_flags &= ~DTRACEBUF_INACTIVE;
	}

	dtrace_interrupt_enable(cookie);
}