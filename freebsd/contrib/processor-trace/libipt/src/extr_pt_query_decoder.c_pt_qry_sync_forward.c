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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * begin; } ;
struct pt_query_decoder {TYPE_1__ config; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * sync; } ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int pt_qry_start (struct pt_query_decoder*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int pt_sync_forward (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int pte_internal ; 
 int pte_invalid ; 
 int ptps_psb ; 

int pt_qry_sync_forward(struct pt_query_decoder *decoder, uint64_t *ip)
{
	const uint8_t *pos, *sync, *begin;
	ptrdiff_t space;
	int errcode;

	if (!decoder)
		return -pte_invalid;

	begin = decoder->config.begin;
	sync = decoder->sync;
	pos = decoder->pos;
	if (!pos)
		pos = begin;

	if (pos == sync)
		pos += ptps_psb;

	if (pos < begin)
		return -pte_internal;

	/* Start a bit earlier so we find PSB that have been partially consumed
	 * by a preceding packet.
	 */
	space = pos - begin;
	if (ptps_psb <= space)
		space = ptps_psb - 1;

	pos -= space;

	errcode = pt_sync_forward(&sync, pos, &decoder->config);
	if (errcode < 0)
		return errcode;

	return pt_qry_start(decoder, sync, ip);
}