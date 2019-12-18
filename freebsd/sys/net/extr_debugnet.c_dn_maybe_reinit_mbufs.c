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
struct TYPE_2__ {int nmbuf; int ncl; int clsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugnet_mbuf_reinit (int,int,int) ; 
 TYPE_1__ dn_hwm ; 
 int /*<<< orphan*/  dn_hwm_lk ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dn_maybe_reinit_mbufs(int nmbuf, int ncl, int clsize)
{
	bool any;

	any = false;
	mtx_lock(&dn_hwm_lk);

	if (nmbuf > dn_hwm.nmbuf) {
		any = true;
		dn_hwm.nmbuf = nmbuf;
	} else
		nmbuf = dn_hwm.nmbuf;

	if (ncl > dn_hwm.ncl) {
		any = true;
		dn_hwm.ncl = ncl;
	} else
		ncl = dn_hwm.ncl;

	if (clsize > dn_hwm.clsize) {
		any = true;
		dn_hwm.clsize = clsize;
	} else
		clsize = dn_hwm.clsize;

	mtx_unlock(&dn_hwm_lk);

	if (any)
		debugnet_mbuf_reinit(nmbuf, ncl, clsize);
}