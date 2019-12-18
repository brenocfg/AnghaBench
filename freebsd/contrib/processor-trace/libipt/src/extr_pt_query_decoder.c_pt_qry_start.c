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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_query_decoder {int /*<<< orphan*/  ip; struct pt_decoder_function* next; int /*<<< orphan*/  config; int /*<<< orphan*/  const* pos; int /*<<< orphan*/  const* sync; } ;
struct pt_decoder_function {int (* decode ) (struct pt_query_decoder*) ;} ;

/* Variables and functions */
 struct pt_decoder_function const pt_decode_psb ; 
 int pt_df_fetch (struct pt_decoder_function**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int pt_last_ip_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_read_ahead (struct pt_query_decoder*) ; 
 int /*<<< orphan*/  pt_qry_reset (struct pt_query_decoder*) ; 
 int pt_qry_status_flags (struct pt_query_decoder*) ; 
 int pte_invalid ; 
 int pte_nosync ; 
 int pts_ip_suppressed ; 
 int stub1 (struct pt_query_decoder*) ; 

__attribute__((used)) static int pt_qry_start(struct pt_query_decoder *decoder, const uint8_t *pos,
			uint64_t *addr)
{
	const struct pt_decoder_function *dfun;
	int status, errcode;

	if (!decoder || !pos)
		return -pte_invalid;

	pt_qry_reset(decoder);

	decoder->sync = pos;
	decoder->pos = pos;

	errcode = pt_df_fetch(&decoder->next, pos, &decoder->config);
	if (errcode)
		return errcode;

	dfun = decoder->next;

	/* We do need to start at a PSB in order to initialize the state. */
	if (dfun != &pt_decode_psb)
		return -pte_nosync;

	/* Decode the PSB+ header to initialize the state. */
	errcode = dfun->decode(decoder);
	if (errcode < 0)
		return errcode;

	/* Fill in the start address.
	 * We do this before reading ahead since the latter may read an
	 * adjacent PSB+ that might change the decoder's IP, causing us
	 * to skip code.
	 */
	if (addr) {
		status = pt_last_ip_query(addr, &decoder->ip);

		/* Make sure we don't clobber it later on. */
		if (!status)
			addr = NULL;
	}

	/* Read ahead until the first query-relevant packet. */
	errcode = pt_qry_read_ahead(decoder);
	if (errcode < 0)
		return errcode;

	/* We return the current decoder status. */
	status = pt_qry_status_flags(decoder);
	if (status < 0)
		return status;

	errcode = pt_last_ip_query(addr, &decoder->ip);
	if (errcode < 0) {
		/* Indicate the missing IP in the status. */
		if (addr)
			status |= pts_ip_suppressed;
	}

	return status;
}