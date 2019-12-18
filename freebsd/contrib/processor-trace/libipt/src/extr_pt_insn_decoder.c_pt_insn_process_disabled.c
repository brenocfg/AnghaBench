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
struct pt_event {scalar_t__ status_update; } ;
struct pt_insn_decoder {scalar_t__ enabled; struct pt_event event; } ;

/* Variables and functions */
 int pte_bad_context ; 
 int pte_internal ; 

__attribute__((used)) static int pt_insn_process_disabled(struct pt_insn_decoder *decoder)
{
	struct pt_event *ev;

	if (!decoder)
		return -pte_internal;

	ev = &decoder->event;

	/* This event can't be a status update. */
	if (ev->status_update)
		return -pte_bad_context;

	/* We must currently be enabled. */
	if (!decoder->enabled)
		return -pte_bad_context;

	/* We preserve @decoder->ip.  This is where we expect tracing to resume
	 * and we'll indicate that on the subsequent enabled event if tracing
	 * actually does resume from there.
	 */
	decoder->enabled = 0;

	return 0;
}