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
typedef  void* tcp_seq ;
struct sack_filter {void* sf_ack; TYPE_1__* sf_blks; int /*<<< orphan*/  sf_used; int /*<<< orphan*/  sf_bits; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {void* start; void* end; } ;

/* Variables and functions */
 size_t SACK_FILTER_BLOCKS ; 
 scalar_t__ SEQ_GT (void*,void*) ; 
 int /*<<< orphan*/  sack_blk_clr (struct sack_filter*,size_t) ; 
 scalar_t__ sack_blk_used (struct sack_filter*,size_t) ; 

__attribute__((used)) static void
sack_filter_prune(struct sack_filter *sf, tcp_seq th_ack)
{
	int32_t i;
	/* start with the oldest */
	for (i = 0; i < SACK_FILTER_BLOCKS; i++) {
		if (sack_blk_used(sf, i)) {
			if (SEQ_GT(th_ack, sf->sf_blks[i].end)) {
				/* This block is consumed */
				sf->sf_bits = sack_blk_clr(sf, i);
				sf->sf_used--;
			} else if (SEQ_GT(th_ack, sf->sf_blks[i].start)) {
				/* Some of it is acked */
				sf->sf_blks[i].start = th_ack;
				/* We could in theory break here, but
				 * there are some broken implementations
				 * that send multiple blocks. We want
				 * to catch them all with similar seq's.
				 */
			}
		}
	}
	sf->sf_ack = th_ack;
}