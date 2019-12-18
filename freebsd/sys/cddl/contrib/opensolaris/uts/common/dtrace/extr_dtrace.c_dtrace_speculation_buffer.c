#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t processorid_t ;
struct TYPE_7__ {int dts_nspeculations; TYPE_2__* dts_speculations; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_8__ {int dtsp_state; TYPE_3__* dtsp_buffer; } ;
typedef  TYPE_2__ dtrace_speculation_t ;
typedef  int dtrace_speculation_state_t ;
typedef  int dtrace_specid_t ;
struct TYPE_9__ {int /*<<< orphan*/  dtb_offset; } ;
typedef  TYPE_3__ dtrace_buffer_t ;
struct TYPE_10__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
#define  DTRACESPEC_ACTIVE 134 
#define  DTRACESPEC_ACTIVEMANY 133 
#define  DTRACESPEC_ACTIVEONE 132 
#define  DTRACESPEC_COMMITTING 131 
#define  DTRACESPEC_COMMITTINGMANY 130 
#define  DTRACESPEC_DISCARDING 129 
#define  DTRACESPEC_INACTIVE 128 
 TYPE_6__* cpu_core ; 
 int dtrace_cas32 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static dtrace_buffer_t *
dtrace_speculation_buffer(dtrace_state_t *state, processorid_t cpuid,
    dtrace_specid_t which)
{
	dtrace_speculation_t *spec;
	dtrace_speculation_state_t current, new = 0;
	dtrace_buffer_t *buf;

	if (which == 0)
		return (NULL);

	if (which > state->dts_nspeculations) {
		cpu_core[cpuid].cpuc_dtrace_flags |= CPU_DTRACE_ILLOP;
		return (NULL);
	}

	spec = &state->dts_speculations[which - 1];
	buf = &spec->dtsp_buffer[cpuid];

	do {
		current = spec->dtsp_state;

		switch (current) {
		case DTRACESPEC_INACTIVE:
		case DTRACESPEC_COMMITTINGMANY:
		case DTRACESPEC_DISCARDING:
			return (NULL);

		case DTRACESPEC_COMMITTING:
			ASSERT(buf->dtb_offset == 0);
			return (NULL);

		case DTRACESPEC_ACTIVEONE:
			/*
			 * This speculation is currently active on one CPU.
			 * Check the offset in the buffer; if it's non-zero,
			 * that CPU must be us (and we leave the state alone).
			 * If it's zero, assume that we're starting on a new
			 * CPU -- and change the state to indicate that the
			 * speculation is active on more than one CPU.
			 */
			if (buf->dtb_offset != 0)
				return (buf);

			new = DTRACESPEC_ACTIVEMANY;
			break;

		case DTRACESPEC_ACTIVEMANY:
			return (buf);

		case DTRACESPEC_ACTIVE:
			new = DTRACESPEC_ACTIVEONE;
			break;

		default:
			ASSERT(0);
		}
	} while (dtrace_cas32((uint32_t *)&spec->dtsp_state,
	    current, new) != current);

	ASSERT(new == DTRACESPEC_ACTIVEONE || new == DTRACESPEC_ACTIVEMANY);
	return (buf);
}