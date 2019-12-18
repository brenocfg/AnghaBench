#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  end; } ;
struct pt_query_decoder {struct pt_decoder_function* next; TYPE_1__ config; int /*<<< orphan*/  pos; } ;
struct pt_decoder_function {int (* decode ) (struct pt_query_decoder*) ;int flags; } ;

/* Variables and functions */
 int pdff_tip ; 
 int pdff_tnt ; 
 int pt_df_fetch (struct pt_decoder_function**,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ pt_qry_will_event (struct pt_query_decoder*) ; 
 int pte_eos ; 
 int pte_internal ; 
 int stub1 (struct pt_query_decoder*) ; 

__attribute__((used)) static int pt_qry_read_ahead(struct pt_query_decoder *decoder)
{
	if (!decoder)
		return -pte_internal;

	for (;;) {
		const struct pt_decoder_function *dfun;
		int errcode;

		errcode = pt_df_fetch(&decoder->next, decoder->pos,
				      &decoder->config);
		if (errcode)
			return errcode;

		dfun = decoder->next;
		if (!dfun)
			return -pte_internal;

		if (!dfun->decode)
			return -pte_internal;

		/* We're done once we reach
		 *
		 * - a branching related packet. */
		if (dfun->flags & (pdff_tip | pdff_tnt))
			return 0;

		/* - an event related packet. */
		if (pt_qry_will_event(decoder))
			return 0;

		/* Decode status update packets. */
		errcode = dfun->decode(decoder);
		if (errcode) {
			/* Ignore truncated status packets at the end.
			 *
			 * Move beyond the packet and clear @decoder->next to
			 * indicate that we were not able to fetch the next
			 * packet.
			 */
			if (errcode == -pte_eos) {
				decoder->pos = decoder->config.end;
				decoder->next = NULL;
			}

			return errcode;
		}
	}
}