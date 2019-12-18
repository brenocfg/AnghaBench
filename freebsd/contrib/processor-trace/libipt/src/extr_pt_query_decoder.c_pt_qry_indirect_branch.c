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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_query_decoder {int /*<<< orphan*/  time; int /*<<< orphan*/  last_time; int /*<<< orphan*/  ip; int /*<<< orphan*/ * event; int /*<<< orphan*/  tnt; struct pt_decoder_function* next; } ;
struct pt_decoder_function {int (* decode ) (struct pt_query_decoder*) ;int flags; } ;

/* Variables and functions */
 int pdff_tip ; 
 int pdff_tnt ; 
 int pt_last_ip_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_provoke_fetch_error (struct pt_query_decoder*) ; 
 int pt_qry_read_ahead (struct pt_query_decoder*) ; 
 int pt_qry_status_flags (struct pt_query_decoder*) ; 
 scalar_t__ pt_qry_will_event (struct pt_query_decoder*) ; 
 int /*<<< orphan*/  pt_tnt_cache_is_empty (int /*<<< orphan*/ *) ; 
 int pte_bad_query ; 
 int pte_eos ; 
 int pte_event_ignored ; 
 int pte_internal ; 
 int pte_invalid ; 
 int pts_ip_suppressed ; 
 int stub1 (struct pt_query_decoder*) ; 

int pt_qry_indirect_branch(struct pt_query_decoder *decoder, uint64_t *addr)
{
	int errcode, flags;

	if (!decoder || !addr)
		return -pte_invalid;

	flags = 0;
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

		/* Clear the decoder's current event so we know when we
		 * accidentally skipped an event.
		 */
		decoder->event = NULL;

		/* We may see a single TNT packet if the current tnt is empty.
		 *
		 * If we see a TNT while the current tnt is not empty, it means
		 * that our user got out of sync. Let's report no data and hope
		 * that our user is able to re-sync.
		 */
		if ((dfun->flags & pdff_tnt) &&
		    !pt_tnt_cache_is_empty(&decoder->tnt))
			return -pte_bad_query;

		/* Apply the decoder function. */
		errcode = dfun->decode(decoder);
		if (errcode)
			return errcode;

		/* If we skipped an event, we're in trouble. */
		if (decoder->event)
			return -pte_event_ignored;

		/* We're done when we found a TIP packet that isn't part of an
		 * event.
		 */
		if (dfun->flags & pdff_tip) {
			uint64_t ip;

			/* We already decoded it, so the branch destination
			 * is stored in the decoder's last ip.
			 */
			errcode = pt_last_ip_query(&ip, &decoder->ip);
			if (errcode < 0)
				flags |= pts_ip_suppressed;
			else
				*addr = ip;

			break;
		}

		/* Read ahead until the next query-relevant packet. */
		errcode = pt_qry_read_ahead(decoder);
		if (errcode)
			return errcode;
	}

	/* Preserve the time at the TIP packet. */
	decoder->last_time = decoder->time;

	/* Read ahead until the next query-relevant packet. */
	errcode = pt_qry_read_ahead(decoder);
	if ((errcode < 0) && (errcode != -pte_eos))
		return errcode;

	flags |= pt_qry_status_flags(decoder);

	return flags;
}