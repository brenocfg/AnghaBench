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
struct pt_query_decoder {int pos; int /*<<< orphan*/  config; int /*<<< orphan*/  tcal; int /*<<< orphan*/  time; } ;
struct pt_packet_tma {int dummy; } ;

/* Variables and functions */
 int pt_pkt_read_tma (struct pt_packet_tma*,int,int /*<<< orphan*/ *) ; 
 int pt_qry_apply_tma (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pt_packet_tma*,int /*<<< orphan*/ *) ; 
 int pte_internal ; 

int pt_qry_decode_tma(struct pt_query_decoder *decoder)
{
	struct pt_packet_tma packet;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_tma(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	errcode = pt_qry_apply_tma(&decoder->time, &decoder->tcal,
				   &packet, &decoder->config);
	if (errcode < 0)
		return errcode;

	decoder->pos += size;
	return 0;
}