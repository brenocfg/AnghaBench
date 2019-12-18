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
struct pt_block_decoder {int status; int /*<<< orphan*/  process_event; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int pte_internal ; 
 int pts_eos ; 
 int pts_ip_suppressed ; 

__attribute__((used)) static int pt_blk_status(const struct pt_block_decoder *decoder, int flags)
{
	int status;

	if (!decoder)
		return -pte_internal;

	status = decoder->status;

	/* Indicate whether tracing is disabled or enabled.
	 *
	 * This duplicates the indication in struct pt_insn and covers the case
	 * where we indicate the status after synchronizing.
	 */
	if (!decoder->enabled)
		flags |= pts_ip_suppressed;

	/* Forward end-of-trace indications.
	 *
	 * Postpone it as long as we're still processing events, though.
	 */
	if ((status & pts_eos) && !decoder->process_event)
		flags |= pts_eos;

	return flags;
}