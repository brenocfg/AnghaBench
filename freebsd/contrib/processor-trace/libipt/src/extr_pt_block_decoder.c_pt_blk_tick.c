#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  void* uint32_t ;
struct TYPE_3__ {scalar_t__ ip; } ;
struct TYPE_4__ {TYPE_1__ tick; } ;
struct pt_event {scalar_t__ tsc; int has_tsc; void* lost_cyc; void* lost_mtc; TYPE_2__ variant; int /*<<< orphan*/  type; } ;
struct pt_block_decoder {int process_event; struct pt_event event; int /*<<< orphan*/  query; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_event*,int /*<<< orphan*/ ,int) ; 
 int pt_qry_time (int /*<<< orphan*/ *,scalar_t__*,void**,void**) ; 
 int pte_internal ; 
 int pte_no_time ; 
 int /*<<< orphan*/  ptev_tick ; 

__attribute__((used)) static int pt_blk_tick(struct pt_block_decoder *decoder, uint64_t ip)
{
	struct pt_event *ev;
	uint64_t tsc;
	uint32_t lost_mtc, lost_cyc;
	int errcode;

	if (!decoder)
		return -pte_internal;

	/* We're not generating tick events if tracing is disabled. */
	if (!decoder->enabled)
		return -pte_internal;

	/* Events already provide a timestamp so there is no need to synthesize
	 * an artificial tick event.  There's no room, either, since this would
	 * overwrite the in-progress event.
	 *
	 * In rare cases where we need to proceed to an event location using
	 * trace this may cause us to miss a timing update if the event is not
	 * forwarded to the user.
	 *
	 * The only case I can come up with at the moment is a MODE.EXEC binding
	 * to the TIP IP of a far branch.
	 */
	if (decoder->process_event)
		return 0;

	errcode = pt_qry_time(&decoder->query, &tsc, &lost_mtc, &lost_cyc);
	if (errcode < 0) {
		/* If we don't have wall-clock time, we use relative time. */
		if (errcode != -pte_no_time)
			return errcode;
	}

	ev = &decoder->event;

	/* We're done if time has not changed since the last event. */
	if (tsc == ev->tsc)
		return 0;

	/* Time has changed so we create a new tick event. */
	memset(ev, 0, sizeof(*ev));
	ev->type = ptev_tick;
	ev->variant.tick.ip = ip;

	/* Indicate if we have wall-clock time or only relative time. */
	if (errcode != -pte_no_time)
		ev->has_tsc = 1;
	ev->tsc = tsc;
	ev->lost_mtc = lost_mtc;
	ev->lost_cyc = lost_cyc;

	/* We now have an event to process. */
	decoder->process_event = 1;

	return 1;
}