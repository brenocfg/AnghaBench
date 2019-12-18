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
struct pt_query_decoder {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int pt_qry_process_pending_psb_events (struct pt_query_decoder*) ; 
 int pte_internal ; 
 scalar_t__ ptps_psbend ; 

int pt_qry_decode_psbend(struct pt_query_decoder *decoder)
{
	int status;

	if (!decoder)
		return -pte_internal;

	status = pt_qry_process_pending_psb_events(decoder);
	if (status < 0)
		return status;

	/* If we had any psb events, we're done for now. */
	if (status)
		return 0;

	/* Skip the psbend extended opcode that we fetched before if no more
	 * psbend events are pending.
	 */
	decoder->pos += ptps_psbend;
	return 0;
}