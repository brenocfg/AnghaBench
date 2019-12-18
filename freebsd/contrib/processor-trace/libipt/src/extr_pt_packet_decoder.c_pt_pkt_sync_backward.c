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
struct TYPE_2__ {int /*<<< orphan*/  const* end; } ;
struct pt_packet_decoder {int /*<<< orphan*/  const* pos; int /*<<< orphan*/  const* sync; TYPE_1__ config; } ;

/* Variables and functions */
 int pt_sync_backward (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int pte_invalid ; 

int pt_pkt_sync_backward(struct pt_packet_decoder *decoder)
{
	const uint8_t *pos, *sync;
	int errcode;

	if (!decoder)
		return -pte_invalid;

	pos = decoder->pos;
	if (!pos)
		pos = decoder->config.end;

	errcode = pt_sync_backward(&sync, pos, &decoder->config);
	if (errcode < 0)
		return errcode;

	decoder->sync = sync;
	decoder->pos = sync;

	return 0;
}