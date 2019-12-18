#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int qidx_t ;
typedef  TYPE_2__* iflib_txq_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {int ift_size; int* ift_txd_size; TYPE_1__* ift_ifdi; } ;
struct TYPE_4__ {scalar_t__ idi_vaddr; } ;

/* Variables and functions */
 scalar_t__ CACHE_PTR_NEXT (scalar_t__) ; 
 scalar_t__ __predict_false (int) ; 

__attribute__((used)) static inline caddr_t
calc_next_txd(iflib_txq_t txq, int cidx, uint8_t qid)
{
	qidx_t size;
	int ntxd;
	caddr_t start, end, cur, next;

	ntxd = txq->ift_size;
	size = txq->ift_txd_size[qid];
	start = txq->ift_ifdi[qid].idi_vaddr;

	if (__predict_false(size == 0))
		return (start);
	cur = start + size*cidx;
	end = start + size*ntxd;
	next = CACHE_PTR_NEXT(cur);
	return (next < end ? next : start);
}