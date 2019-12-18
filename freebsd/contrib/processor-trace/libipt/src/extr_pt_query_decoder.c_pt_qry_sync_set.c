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
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * begin; } ;
struct pt_query_decoder {TYPE_1__ config; } ;

/* Variables and functions */
 int pt_qry_start (struct pt_query_decoder*,int /*<<< orphan*/  const*,int*) ; 
 int pt_sync_set (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int pte_invalid ; 

int pt_qry_sync_set(struct pt_query_decoder *decoder, uint64_t *ip,
		    uint64_t offset)
{
	const uint8_t *sync, *pos;
	int errcode;

	if (!decoder)
		return -pte_invalid;

	pos = decoder->config.begin + offset;

	errcode = pt_sync_set(&sync, pos, &decoder->config);
	if (errcode < 0)
		return errcode;

	return pt_qry_start(decoder, sync, ip);
}