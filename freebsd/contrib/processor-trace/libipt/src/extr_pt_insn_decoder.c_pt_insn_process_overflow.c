#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long long ip; } ;
struct TYPE_4__ {TYPE_1__ overflow; } ;
struct pt_event {TYPE_2__ variant; scalar_t__ ip_suppressed; scalar_t__ status_update; } ;
struct pt_insn_decoder {int enabled; unsigned long long ip; scalar_t__ speculative; struct pt_event event; } ;

/* Variables and functions */
 int pte_bad_context ; 
 int pte_internal ; 

__attribute__((used)) static int pt_insn_process_overflow(struct pt_insn_decoder *decoder)
{
	struct pt_event *ev;

	if (!decoder)
		return -pte_internal;

	ev = &decoder->event;

	/* This event can't be a status update. */
	if (ev->status_update)
		return -pte_bad_context;

	/* If the IP is suppressed, the overflow resolved while tracing was
	 * disabled.  Otherwise it resolved while tracing was enabled.
	 */
	if (ev->ip_suppressed) {
		/* Tracing is disabled.
		 *
		 * It doesn't make sense to preserve the previous IP.  This will
		 * just be misleading.  Even if tracing had been disabled
		 * before, as well, we might have missed the re-enable in the
		 * overflow.
		 */
		decoder->enabled = 0;
		decoder->ip = 0ull;
	} else {
		/* Tracing is enabled and we're at the IP at which the overflow
		 * resolved.
		 */
		decoder->ip = ev->variant.overflow.ip;
		decoder->enabled = 1;
	}

	/* We don't know the TSX state.  Let's assume we execute normally.
	 *
	 * We also don't know the execution mode.  Let's keep what we have
	 * in case we don't get an update before we have to decode the next
	 * instruction.
	 */
	decoder->speculative = 0;

	return 0;
}