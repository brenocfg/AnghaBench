#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qidx_t ;
typedef  TYPE_1__* iflib_txq_t ;
struct TYPE_4__ {int ift_size; int ift_in_use; } ;

/* Variables and functions */
 int TXD_NOTIFY_COUNT (TYPE_1__*) ; 

__attribute__((used)) static inline qidx_t
txq_max_rs_deferred(iflib_txq_t txq)
{
	qidx_t notify_count = TXD_NOTIFY_COUNT(txq);
	qidx_t minthresh = txq->ift_size / 8;
	if (txq->ift_in_use > 4*minthresh)
		return (notify_count);
	if (txq->ift_in_use > 2*minthresh)
		return (notify_count >> 1);
	if (txq->ift_in_use > minthresh)
		return (notify_count >> 2);
	return (2);
}