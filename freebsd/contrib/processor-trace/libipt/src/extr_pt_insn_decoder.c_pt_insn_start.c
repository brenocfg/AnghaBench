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
struct pt_insn_decoder {int status; int enabled; } ;

/* Variables and functions */
 int pt_insn_check_ip_event (struct pt_insn_decoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int pts_ip_suppressed ; 

__attribute__((used)) static int pt_insn_start(struct pt_insn_decoder *decoder, int status)
{
	if (!decoder)
		return -pte_internal;

	if (status < 0)
		return status;

	decoder->status = status;

	if (!(status & pts_ip_suppressed))
		decoder->enabled = 1;

	/* Process any initial events.
	 *
	 * Some events are processed after proceeding to the next IP in order to
	 * indicate things like tracing disable or trace stop in the preceding
	 * instruction.  Those events will be processed without such an
	 * indication before decoding the current instruction.
	 *
	 * We do this already here so we can indicate user-events that precede
	 * the first instruction.
	 */
	return pt_insn_check_ip_event(decoder, NULL, NULL);
}