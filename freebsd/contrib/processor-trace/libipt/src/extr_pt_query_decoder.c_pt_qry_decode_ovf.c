#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_time_cal {int dummy; } ;
struct pt_time {int dummy; } ;
struct TYPE_9__ {scalar_t__ apl12; scalar_t__ apl11; scalar_t__ skd010; } ;
struct TYPE_6__ {scalar_t__ keep_tcal_on_ovf; } ;
struct TYPE_7__ {TYPE_1__ query; } ;
struct TYPE_8__ {TYPE_2__ variant; } ;
struct TYPE_10__ {TYPE_4__ errata; TYPE_3__ flags; } ;
struct pt_query_decoder {TYPE_5__ config; int /*<<< orphan*/  pos; struct pt_time_cal tcal; struct pt_time time; } ;

/* Variables and functions */
 int pt_qry_event_ovf_disabled (struct pt_query_decoder*) ; 
 int pt_qry_event_ovf_enabled (struct pt_query_decoder*) ; 
 int pt_qry_find_ovf_fup (struct pt_query_decoder*) ; 
 int pt_qry_handle_apl11 (struct pt_query_decoder*) ; 
 int pt_qry_handle_apl12 (struct pt_query_decoder*,unsigned int) ; 
 int pt_qry_handle_skd010 (struct pt_query_decoder*) ; 
 int pt_qry_process_pending_psb_events (struct pt_query_decoder*) ; 
 int /*<<< orphan*/  pt_qry_reset (struct pt_query_decoder*) ; 
 int pt_tcal_update_ovf (struct pt_time_cal*,TYPE_5__*) ; 
 int pte_bad_context ; 
 int pte_eos ; 
 int pte_internal ; 
 scalar_t__ ptps_ovf ; 

int pt_qry_decode_ovf(struct pt_query_decoder *decoder)
{
	struct pt_time_cal tcal;
	struct pt_time time;
	int status, offset;

	if (!decoder)
		return -pte_internal;

	status = pt_qry_process_pending_psb_events(decoder);
	if (status < 0)
		return status;

	/* If we have any pending psbend events, we're done for now. */
	if (status)
		return 0;

	/* Reset the decoder state but preserve timing. */
	time = decoder->time;
	tcal = decoder->tcal;

	pt_qry_reset(decoder);

	decoder->time = time;
	if (decoder->config.flags.variant.query.keep_tcal_on_ovf) {
		status = pt_tcal_update_ovf(&tcal, &decoder->config);
		if (status < 0)
			return status;

		decoder->tcal = tcal;
	}

	/* We must consume the OVF before we search for the binding packet. */
	decoder->pos += ptps_ovf;

	/* Overflow binds to either FUP or TIP.PGE.
	 *
	 * If the overflow can be resolved while PacketEn=1 it binds to FUP.  We
	 * can see timing packets between OVF anf FUP but that's it.
	 *
	 * Otherwise, PacketEn will be zero when the overflow resolves and OVF
	 * binds to TIP.PGE.  There can be packets between OVF and TIP.PGE that
	 * do not depend on PacketEn.
	 *
	 * We don't need to decode everything until TIP.PGE, however.  As soon
	 * as we see a non-timing non-FUP packet, we know that tracing has been
	 * disabled before the overflow resolves.
	 */
	offset = pt_qry_find_ovf_fup(decoder);
	if (offset <= 0) {
		/* Check for erratum SKD010.
		 *
		 * The FUP may have been dropped.  If we can figure out that
		 * tracing is enabled and hence the FUP is missing, we resume
		 * at a later packet and a different IP.
		 */
		if (decoder->config.errata.skd010) {
			status = pt_qry_handle_skd010(decoder);
			if (status <= 0)
				return status;
		}

		/* Check for erratum APL11.
		 *
		 * We may have gotten an extra TIP.PGD, which should be
		 * diagnosed by our search for a subsequent FUP.
		 */
		if (decoder->config.errata.apl11 &&
		    (offset == -pte_bad_context)) {
			status = pt_qry_handle_apl11(decoder);
			if (status <= 0)
				return status;
		}

		/* Report the original error from searching for the FUP packet
		 * if we were not able to fix the trace.
		 *
		 * We treat an overflow at the end of the trace as standalone.
		 */
		if (offset < 0 && offset != -pte_eos)
			return offset;

		return pt_qry_event_ovf_disabled(decoder);
	} else {
		/* Check for erratum APL12.
		 *
		 * We may get an extra FUP even though the overflow resolved
		 * with tracing disabled.
		 */
		if (decoder->config.errata.apl12) {
			status = pt_qry_handle_apl12(decoder,
						     (unsigned int) offset);
			if (status <= 0)
				return status;
		}

		return pt_qry_event_ovf_enabled(decoder);
	}
}