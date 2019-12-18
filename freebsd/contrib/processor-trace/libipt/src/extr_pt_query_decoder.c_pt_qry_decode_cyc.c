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
struct TYPE_2__ {scalar_t__ skd007; } ;
struct pt_config {TYPE_1__ errata; } ;
struct pt_query_decoder {int pos; int /*<<< orphan*/  tcal; int /*<<< orphan*/  time; struct pt_config config; } ;
struct pt_packet_cyc {int dummy; } ;

/* Variables and functions */
 int check_erratum_skd007 (struct pt_query_decoder*,struct pt_packet_cyc*,int) ; 
 int pt_pkt_read_cyc (struct pt_packet_cyc*,int,struct pt_config*) ; 
 int pt_qry_apply_cyc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pt_packet_cyc*,struct pt_config*) ; 
 int pte_internal ; 

int pt_qry_decode_cyc(struct pt_query_decoder *decoder)
{
	struct pt_packet_cyc packet;
	struct pt_config *config;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	config = &decoder->config;

	size = pt_pkt_read_cyc(&packet, decoder->pos, config);
	if (size < 0)
		return size;

	if (config->errata.skd007) {
		errcode = check_erratum_skd007(decoder, &packet, size);
		if (errcode < 0)
			return errcode;

		/* If the erratum hits, we ignore the partial CYC and instead
		 * process the OVF following/overlapping it.
		 */
		if (errcode) {
			/* We skip the first byte of the CYC, which brings us
			 * to the beginning of the OVF packet.
			 */
			decoder->pos += 1;
			return 0;
		}
	}

	errcode = pt_qry_apply_cyc(&decoder->time, &decoder->tcal,
				   &packet, config);
	if (errcode < 0)
		return errcode;

	decoder->pos += size;
	return 0;
}