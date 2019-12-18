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
typedef  int /*<<< orphan*/  const uint8_t ;
struct pt_query_decoder {int /*<<< orphan*/ * next; int /*<<< orphan*/  evq; int /*<<< orphan*/  const* pos; int /*<<< orphan*/  config; int /*<<< orphan*/  tcal; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_psbend ; 
 int /*<<< orphan*/  pt_decode_psb ; 
 int /*<<< orphan*/  pt_evq_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_pkt_read_psb (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int pt_qry_read_psb_header (struct pt_query_decoder*) ; 
 int pt_tcal_update_psb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_internal ; 

int pt_qry_decode_psb(struct pt_query_decoder *decoder)
{
	const uint8_t *pos;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	pos = decoder->pos;

	size = pt_pkt_read_psb(pos, &decoder->config);
	if (size < 0)
		return size;

	errcode = pt_tcal_update_psb(&decoder->tcal, &decoder->config);
	if (errcode < 0)
		return errcode;

	decoder->pos += size;

	errcode = pt_qry_read_psb_header(decoder);
	if (errcode < 0) {
		/* Move back to the PSB so we have a chance to recover and
		 * continue decoding.
		 */
		decoder->pos = pos;

		/* Clear any PSB+ events that have already been queued. */
		(void) pt_evq_clear(&decoder->evq, evb_psbend);

		/* Reset the decoder's decode function. */
		decoder->next = &pt_decode_psb;

		return errcode;
	}

	/* The next packet following the PSB header will be of type PSBEND.
	 *
	 * Decoding this packet will publish the PSB events what have been
	 * accumulated while reading the PSB header.
	 */
	return 0;
}