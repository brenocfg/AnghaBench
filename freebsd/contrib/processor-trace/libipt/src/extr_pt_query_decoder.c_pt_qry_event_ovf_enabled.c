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
struct pt_query_decoder {int enabled; int /*<<< orphan*/  evq; } ;
struct pt_event {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_fup ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_overflow ; 

__attribute__((used)) static int pt_qry_event_ovf_enabled(struct pt_query_decoder *decoder)
{
	struct pt_event *ev;

	if (!decoder)
		return -pte_internal;

	ev = pt_evq_enqueue(&decoder->evq, evb_fup);
	if (!ev)
		return -pte_internal;

	ev->type = ptev_overflow;

	decoder->enabled = 1;

	return pt_qry_event_time(ev, decoder);
}