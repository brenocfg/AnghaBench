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
struct pt_block_decoder {int status; int enabled; } ;

/* Variables and functions */
 int pt_blk_proceed_trailing_event (struct pt_block_decoder*,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int pts_ip_suppressed ; 

__attribute__((used)) static int pt_blk_start(struct pt_block_decoder *decoder, int status)
{
	if (!decoder)
		return -pte_internal;

	if (status < 0)
		return status;

	decoder->status = status;
	if (!(status & pts_ip_suppressed))
		decoder->enabled = 1;

	/* We will always have an event.
	 *
	 * If we synchronized onto an empty PSB+, tracing is disabled and we'll
	 * process events until the enabled event.
	 *
	 * If tracing is enabled, PSB+ must at least provide the execution mode,
	 * which we're going to forward to the user.
	 */
	return pt_blk_proceed_trailing_event(decoder, NULL);
}