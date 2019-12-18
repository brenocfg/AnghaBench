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
struct memory_type {TYPE_2__* mt_percpu_cache; TYPE_1__* mt_percpu_alloc; scalar_t__ mt_kegfree; scalar_t__ mt_zonefree; scalar_t__ mt_sleeps; scalar_t__ mt_failures; scalar_t__ mt_free; scalar_t__ mt_count; scalar_t__ mt_bytes; scalar_t__ mt_numfrees; scalar_t__ mt_numallocs; scalar_t__ mt_memfreed; scalar_t__ mt_memalloced; scalar_t__ mt_size; scalar_t__ mt_sizemask; scalar_t__ mt_byteslimit; scalar_t__ mt_countlimit; } ;
struct TYPE_4__ {scalar_t__ mtp_free; } ;
struct TYPE_3__ {scalar_t__ mtp_sizemask; scalar_t__ mtp_numfrees; scalar_t__ mtp_numallocs; scalar_t__ mtp_memfreed; scalar_t__ mtp_memalloced; } ;

/* Variables and functions */

void
_memstat_mt_reset_stats(struct memory_type *mtp, int maxcpus)
{
	int i;

	mtp->mt_countlimit = 0;
	mtp->mt_byteslimit = 0;
	mtp->mt_sizemask = 0;
	mtp->mt_size = 0;

	mtp->mt_memalloced = 0;
	mtp->mt_memfreed = 0;
	mtp->mt_numallocs = 0;
	mtp->mt_numfrees = 0;
	mtp->mt_bytes = 0;
	mtp->mt_count = 0;
	mtp->mt_free = 0;
	mtp->mt_failures = 0;
	mtp->mt_sleeps = 0;

	mtp->mt_zonefree = 0;
	mtp->mt_kegfree = 0;

	for (i = 0; i < maxcpus; i++) {
		mtp->mt_percpu_alloc[i].mtp_memalloced = 0;
		mtp->mt_percpu_alloc[i].mtp_memfreed = 0;
		mtp->mt_percpu_alloc[i].mtp_numallocs = 0;
		mtp->mt_percpu_alloc[i].mtp_numfrees = 0;
		mtp->mt_percpu_alloc[i].mtp_sizemask = 0;
		mtp->mt_percpu_cache[i].mtp_free = 0;
	}
}