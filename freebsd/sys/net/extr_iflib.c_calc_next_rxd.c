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
typedef  int qidx_t ;
typedef  TYPE_2__* iflib_fl_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {int ifl_size; int ifl_rxd_size; TYPE_1__* ifl_ifdi; } ;
struct TYPE_4__ {scalar_t__ idi_vaddr; } ;

/* Variables and functions */
 scalar_t__ CACHE_PTR_NEXT (scalar_t__) ; 
 scalar_t__ __predict_false (int) ; 

__attribute__((used)) static inline caddr_t
calc_next_rxd(iflib_fl_t fl, int cidx)
{
	qidx_t size;
	int nrxd;
	caddr_t start, end, cur, next;

	nrxd = fl->ifl_size;
	size = fl->ifl_rxd_size;
	start = fl->ifl_ifdi->idi_vaddr;

	if (__predict_false(size == 0))
		return (start);
	cur = start + size*cidx;
	end = start + size*nrxd;
	next = CACHE_PTR_NEXT(cur);
	return (next < end ? next : start);
}