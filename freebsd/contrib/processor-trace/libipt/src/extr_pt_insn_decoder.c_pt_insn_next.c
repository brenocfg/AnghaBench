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
struct pt_mapped_section {int dummy; } ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn_decoder {int status; int /*<<< orphan*/  mode; int /*<<< orphan*/  ip; scalar_t__ speculative; int /*<<< orphan*/  enabled; } ;
struct pt_insn {int speculative; int isid; int /*<<< orphan*/  mode; int /*<<< orphan*/  ip; } ;
typedef  int /*<<< orphan*/  insn ;

/* Variables and functions */
 int insn_to_user (struct pt_insn*,size_t,struct pt_insn*) ; 
 int /*<<< orphan*/  memset (struct pt_insn*,int /*<<< orphan*/ ,int) ; 
 int pt_insn_check_insn_event (struct pt_insn_decoder*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_check_ip_event (struct pt_insn_decoder*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_decode_cached (struct pt_insn_decoder*,struct pt_mapped_section const*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_msec_lookup (struct pt_insn_decoder*,struct pt_mapped_section const**) ; 
 int pt_insn_proceed (struct pt_insn_decoder*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pte_eos ; 
 int pte_invalid ; 
 int pte_no_enable ; 
 int pte_nomap ; 
 int pts_eos ; 
 int pts_event_pending ; 

int pt_insn_next(struct pt_insn_decoder *decoder, struct pt_insn *uinsn,
		 size_t size)
{
	const struct pt_mapped_section *msec;
	struct pt_insn_ext iext;
	struct pt_insn insn, *pinsn;
	int status, isid;

	if (!uinsn || !decoder)
		return -pte_invalid;

	/* Tracing must be enabled.
	 *
	 * If it isn't we should be processing events until we either run out of
	 * trace or process a tracing enabled event.
	 */
	if (!decoder->enabled) {
		if (decoder->status & pts_eos)
			return -pte_eos;

		return -pte_no_enable;
	}

	pinsn = size == sizeof(insn) ? uinsn : &insn;

	/* Zero-initialize the instruction in case of error returns. */
	memset(pinsn, 0, sizeof(*pinsn));

	/* Fill in a few things from the current decode state.
	 *
	 * This reflects the state of the last pt_insn_next(), pt_insn_event()
	 * or pt_insn_start() call.
	 */
	if (decoder->speculative)
		pinsn->speculative = 1;
	pinsn->ip = decoder->ip;
	pinsn->mode = decoder->mode;

	isid = pt_insn_msec_lookup(decoder, &msec);
	if (isid < 0) {
		if (isid != -pte_nomap)
			return isid;

		msec = NULL;
	}

	/* We set an incorrect isid if @msec is NULL.  This will be corrected
	 * when we read the memory from the image later on.
	 */
	pinsn->isid = isid;

	status = pt_insn_decode_cached(decoder, msec, pinsn, &iext);
	if (status < 0) {
		/* Provide the incomplete instruction - the IP and mode fields
		 * are valid and may help diagnose the error.
		 */
		(void) insn_to_user(uinsn, size, pinsn);
		return status;
	}

	/* Provide the decoded instruction to the user.  It won't change during
	 * event processing.
	 */
	status = insn_to_user(uinsn, size, pinsn);
	if (status < 0)
		return status;

	/* Check for events that bind to the current instruction.
	 *
	 * If an event is indicated, we're done.
	 */
	status = pt_insn_check_insn_event(decoder, pinsn, &iext);
	if (status != 0) {
		if (status < 0)
			return status;

		if (status & pts_event_pending)
			return status;
	}

	/* Determine the next instruction's IP. */
	status = pt_insn_proceed(decoder, pinsn, &iext);
	if (status < 0)
		return status;

	/* Indicate events that bind to the new IP.
	 *
	 * Although we only look at the IP for binding events, we pass the
	 * decoded instruction in order to handle errata.
	 */
	return pt_insn_check_ip_event(decoder, pinsn, &iext);
}