#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int spa_lowmem_last_txg; int spa_lowmem_page_load; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCSTAT_INCR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ERESTART ; 
 int MAX (int,int) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int arc_lotsfree_percent ; 
 scalar_t__ arc_reclaim_needed () ; 
 int /*<<< orphan*/  arcstat_memory_throttle_count ; 
 int /*<<< orphan*/  atomic_add_64 (int*,int) ; 
 scalar_t__ curproc ; 
 int freemem ; 
 int minfree ; 
 scalar_t__ pageproc ; 
 scalar_t__ physmem ; 
 int ptob (int) ; 
 int /*<<< orphan*/  uma_avail () ; 

__attribute__((used)) static int
arc_memory_throttle(spa_t *spa, uint64_t reserve, uint64_t txg)
{
#ifdef _KERNEL
	uint64_t available_memory = ptob(freemem);

#if defined(__i386) || !defined(UMA_MD_SMALL_ALLOC)
	available_memory = MIN(available_memory, uma_avail());
#endif

	if (freemem > (uint64_t)physmem * arc_lotsfree_percent / 100)
		return (0);

	if (txg > spa->spa_lowmem_last_txg) {
		spa->spa_lowmem_last_txg = txg;
		spa->spa_lowmem_page_load = 0;
	}
	/*
	 * If we are in pageout, we know that memory is already tight,
	 * the arc is already going to be evicting, so we just want to
	 * continue to let page writes occur as quickly as possible.
	 */
	if (curproc == pageproc) {
		if (spa->spa_lowmem_page_load >
		    MAX(ptob(minfree), available_memory) / 4)
			return (SET_ERROR(ERESTART));
		/* Note: reserve is inflated, so we deflate */
		atomic_add_64(&spa->spa_lowmem_page_load, reserve / 8);
		return (0);
	} else if (spa->spa_lowmem_page_load > 0 && arc_reclaim_needed()) {
		/* memory is low, delay before restarting */
		ARCSTAT_INCR(arcstat_memory_throttle_count, 1);
		return (SET_ERROR(EAGAIN));
	}
	spa->spa_lowmem_page_load = 0;
#endif /* _KERNEL */
	return (0);
}