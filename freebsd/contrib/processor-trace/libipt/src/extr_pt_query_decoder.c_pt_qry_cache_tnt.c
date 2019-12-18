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
struct pt_query_decoder {int /*<<< orphan*/  time; int /*<<< orphan*/  last_time; int /*<<< orphan*/ * event; struct pt_decoder_function* next; } ;
struct pt_decoder_function {int (* decode ) (struct pt_query_decoder*) ;int flags; } ;

/* Variables and functions */
 int pdff_tip ; 
 int pdff_tnt ; 
 int pt_qry_provoke_fetch_error (struct pt_query_decoder*) ; 
 int pt_qry_read_ahead (struct pt_query_decoder*) ; 
 scalar_t__ pt_qry_will_event (struct pt_query_decoder*) ; 
 int pte_bad_query ; 
 int pte_eos ; 
 int pte_event_ignored ; 
 int pte_internal ; 
 int stub1 (struct pt_query_decoder*) ; 

__attribute__((used)) static int pt_qry_cache_tnt(struct pt_query_decoder *decoder)
{
	int errcode;

	if (!decoder)
		return -pte_internal;

	for (;;) {
		const struct pt_decoder_function *dfun;

		dfun = decoder->next;
		if (!dfun)
			return pt_qry_provoke_fetch_error(decoder);

		if (!dfun->decode)
			return -pte_internal;

		/* There's an event ahead of us. */
		if (pt_qry_will_event(decoder))
			return -pte_bad_query;

		/* Diagnose a TIP that has not been part of an event. */
		if (dfun->flags & pdff_tip)
			return -pte_bad_query;

		/* Clear the decoder's current event so we know when we
		 * accidentally skipped an event.
		 */
		decoder->event = NULL;

		/* Apply the decoder function. */
		errcode = dfun->decode(decoder);
		if (errcode)
			return errcode;

		/* If we skipped an event, we're in trouble. */
		if (decoder->event)
			return -pte_event_ignored;

		/* We're done when we decoded a TNT packet. */
		if (dfun->flags & pdff_tnt)
			break;

		/* Read ahead until the next query-relevant packet. */
		errcode = pt_qry_read_ahead(decoder);
		if (errcode)
			return errcode;
	}

	/* Preserve the time at the TNT packet. */
	decoder->last_time = decoder->time;

	/* Read ahead until the next query-relevant packet. */
	errcode = pt_qry_read_ahead(decoder);
	if ((errcode < 0) && (errcode != -pte_eos))
		return errcode;

	return 0;
}