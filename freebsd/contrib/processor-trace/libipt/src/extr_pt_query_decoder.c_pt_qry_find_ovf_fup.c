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
typedef  scalar_t__ uint64_t ;
struct pt_query_decoder {int /*<<< orphan*/  config; } ;
struct pt_packet_decoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  pt_pkt_decoder_fini (struct pt_packet_decoder*) ; 
 int pt_pkt_decoder_init (struct pt_packet_decoder*,int /*<<< orphan*/ *) ; 
 int pt_pkt_find_ovf_fup (struct pt_packet_decoder*) ; 
 int pt_pkt_get_offset (struct pt_packet_decoder*,scalar_t__*) ; 
 int pt_pkt_sync_set (struct pt_packet_decoder*,scalar_t__) ; 
 int pt_qry_get_offset (struct pt_query_decoder const*,scalar_t__*) ; 
 int pte_internal ; 
 int pte_overflow ; 

__attribute__((used)) static int pt_qry_find_ovf_fup(const struct pt_query_decoder *decoder)
{
	struct pt_packet_decoder pkt;
	uint64_t begin, end, offset;
	int status;

	if (!decoder)
		return -pte_internal;

	status = pt_qry_get_offset(decoder, &begin);
	if (status < 0)
		return status;

	status = pt_pkt_decoder_init(&pkt, &decoder->config);
	if (status < 0)
		return status;

	status = pt_pkt_sync_set(&pkt, begin);
	if (status >= 0) {
		status = pt_pkt_find_ovf_fup(&pkt);
		if (status > 0) {
			status = pt_pkt_get_offset(&pkt, &end);
			if (status < 0)
				return status;

			if (end <= begin)
				return -pte_overflow;

			offset = end - begin;
			if (INT_MAX < offset)
				return -pte_overflow;

			status = (int) offset;
		}
	}

	pt_pkt_decoder_fini(&pkt);
	return status;
}