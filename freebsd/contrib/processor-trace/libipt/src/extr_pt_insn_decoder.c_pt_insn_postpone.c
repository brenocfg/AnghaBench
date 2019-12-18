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
struct pt_insn_decoder {int process_insn; struct pt_insn_ext iext; struct pt_insn insn; } ;

/* Variables and functions */
 int pt_insn_status (struct pt_insn_decoder*,int /*<<< orphan*/ ) ; 
 int pte_internal ; 
 int /*<<< orphan*/  pts_event_pending ; 

__attribute__((used)) static int pt_insn_postpone(struct pt_insn_decoder *decoder,
			    const struct pt_insn *insn,
			    const struct pt_insn_ext *iext)
{
	if (!decoder || !insn || !iext)
		return -pte_internal;

	if (!decoder->process_insn) {
		decoder->process_insn = 1;
		decoder->insn = *insn;
		decoder->iext = *iext;
	}

	return pt_insn_status(decoder, pts_event_pending);
}