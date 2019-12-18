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
struct netmap_kring {int /*<<< orphan*/  rtail; int /*<<< orphan*/  rcur; int /*<<< orphan*/  rhead; int /*<<< orphan*/  nr_hwtail; int /*<<< orphan*/  nr_hwcur; int /*<<< orphan*/  name; TYPE_1__* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  nm_prdis (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
nm_sync_finalize(struct netmap_kring *kring)
{
	/*
	 * Update ring tail to what the kernel knows
	 * After txsync: head/rhead/hwcur might be behind cur/rcur
	 * if no carrier.
	 */
	kring->ring->tail = kring->rtail = kring->nr_hwtail;

	nm_prdis(5, "%s now hwcur %d hwtail %d head %d cur %d tail %d",
		kring->name, kring->nr_hwcur, kring->nr_hwtail,
		kring->rhead, kring->rcur, kring->rtail);
}