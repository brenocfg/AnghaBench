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
struct TYPE_3__ {scalar_t__ ip; } ;
struct TYPE_4__ {TYPE_1__ async_paging; } ;
struct pt_event {TYPE_2__ variant; scalar_t__ ip_suppressed; } ;
struct pt_block_decoder {scalar_t__ ip; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_to_ip_with_trace (struct pt_block_decoder*,struct pt_block*,scalar_t__) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_proceed_to_async_paging(struct pt_block_decoder *decoder,
					  struct pt_block *block,
					  const struct pt_event *ev)
{
	int status;

	if (!decoder || !ev)
		return -pte_internal;

	/* Apply the event immediately if we don't have an IP. */
	if (ev->ip_suppressed)
		return 1;

	status = pt_blk_proceed_to_ip_with_trace(decoder, block,
						 ev->variant.async_paging.ip);
	if (status < 0)
		return status;

	/* We may have reached the IP. */
	return (decoder->ip == ev->variant.async_paging.ip ? 1 : 0);
}