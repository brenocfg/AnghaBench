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
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int dummy; } ;
struct pt_block_decoder {int status; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int pt_blk_next_ip (int /*<<< orphan*/ *,struct pt_block_decoder*,struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pte_internal ; 
 int pte_noip ; 
 int pts_ip_suppressed ; 

__attribute__((used)) static int pt_blk_proceed_with_trace(struct pt_block_decoder *decoder,
				     const struct pt_insn *insn,
				     const struct pt_insn_ext *iext)
{
	int status;

	if (!decoder)
		return -pte_internal;

	status = pt_blk_next_ip(&decoder->ip, decoder, insn, iext);
	if (status < 0)
		return status;

	/* Preserve the query decoder's response which indicates upcoming
	 * events.
	 */
	decoder->status = status;

	/* We do need an IP in order to proceed. */
	if (status & pts_ip_suppressed)
		return -pte_noip;

	return 0;
}