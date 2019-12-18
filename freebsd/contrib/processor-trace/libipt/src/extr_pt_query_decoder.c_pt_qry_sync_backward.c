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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  const* end; } ;
struct pt_query_decoder {int /*<<< orphan*/  const* pos; TYPE_1__ config; } ;

/* Variables and functions */
 int pt_qry_start (struct pt_query_decoder*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int pt_sync_backward (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int pte_eos ; 
 int pte_invalid ; 

int pt_qry_sync_backward(struct pt_query_decoder *decoder, uint64_t *ip)
{
	const uint8_t *start, *sync;
	int errcode;

	if (!decoder)
		return -pte_invalid;

	start = decoder->pos;
	if (!start)
		start = decoder->config.end;

	sync = start;
	for (;;) {
		errcode = pt_sync_backward(&sync, sync, &decoder->config);
		if (errcode < 0)
			return errcode;

		errcode = pt_qry_start(decoder, sync, ip);
		if (errcode < 0) {
			/* Ignore incomplete trace segments at the end.  We need
			 * a full PSB+ to start decoding.
			 */
			if (errcode == -pte_eos)
				continue;

			return errcode;
		}

		/* An empty trace segment in the middle of the trace might bring
		 * us back to where we started.
		 *
		 * We're done when we reached a new position.
		 */
		if (decoder->pos != start)
			break;
	}

	return 0;
}