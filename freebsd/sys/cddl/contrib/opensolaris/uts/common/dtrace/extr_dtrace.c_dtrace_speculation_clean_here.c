#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t processorid_t ;
struct TYPE_6__ {size_t dts_nspeculations; TYPE_2__* dts_speculations; TYPE_3__* dts_buffer; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_7__ {scalar_t__ dtsp_state; TYPE_3__* dtsp_buffer; } ;
typedef  TYPE_2__ dtrace_speculation_t ;
typedef  size_t dtrace_specid_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_8__ {scalar_t__ dtb_offset; int /*<<< orphan*/ * dtb_tomax; } ;
typedef  TYPE_3__ dtrace_buffer_t ;

/* Variables and functions */
 scalar_t__ DTRACESPEC_COMMITTINGMANY ; 
 scalar_t__ DTRACESPEC_DISCARDING ; 
 size_t curcpu ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_speculation_commit (TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static void
dtrace_speculation_clean_here(dtrace_state_t *state)
{
	dtrace_icookie_t cookie;
	processorid_t cpu = curcpu;
	dtrace_buffer_t *dest = &state->dts_buffer[cpu];
	dtrace_specid_t i;

	cookie = dtrace_interrupt_disable();

	if (dest->dtb_tomax == NULL) {
		dtrace_interrupt_enable(cookie);
		return;
	}

	for (i = 0; i < state->dts_nspeculations; i++) {
		dtrace_speculation_t *spec = &state->dts_speculations[i];
		dtrace_buffer_t *src = &spec->dtsp_buffer[cpu];

		if (src->dtb_tomax == NULL)
			continue;

		if (spec->dtsp_state == DTRACESPEC_DISCARDING) {
			src->dtb_offset = 0;
			continue;
		}

		if (spec->dtsp_state != DTRACESPEC_COMMITTINGMANY)
			continue;

		if (src->dtb_offset == 0)
			continue;

		dtrace_speculation_commit(state, cpu, i + 1);
	}

	dtrace_interrupt_enable(cookie);
}