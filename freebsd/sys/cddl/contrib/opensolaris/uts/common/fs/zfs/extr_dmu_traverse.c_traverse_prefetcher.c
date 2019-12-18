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
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_3__ {scalar_t__ pd_bytes_fetched; int /*<<< orphan*/  pd_mtx; int /*<<< orphan*/  pd_cv; scalar_t__ pd_cancel; } ;
typedef  TYPE_1__ prefetch_data_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int arc_flags_t ;

/* Variables and functions */
 int ARC_FLAG_NOWAIT ; 
 int ARC_FLAG_PREFETCH ; 
 int ARC_FLAG_PRESCIENT_PREFETCH ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_GET_LSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EINTR ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_ASYNC_READ ; 
 int /*<<< orphan*/  arc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch_needed (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ zfs_pd_bytes_max ; 

__attribute__((used)) static int
traverse_prefetcher(spa_t *spa, zilog_t *zilog, const blkptr_t *bp,
    const zbookmark_phys_t *zb, const dnode_phys_t *dnp, void *arg)
{
	prefetch_data_t *pfd = arg;
	arc_flags_t aflags = ARC_FLAG_NOWAIT | ARC_FLAG_PREFETCH |
	    ARC_FLAG_PRESCIENT_PREFETCH;
	
	ASSERT(pfd->pd_bytes_fetched >= 0);
	if (bp == NULL)
		return (0);
	if (pfd->pd_cancel)
		return (SET_ERROR(EINTR));

	if (!prefetch_needed(pfd, bp))
		return (0);

	mutex_enter(&pfd->pd_mtx);
	while (!pfd->pd_cancel && pfd->pd_bytes_fetched >= zfs_pd_bytes_max)
		cv_wait(&pfd->pd_cv, &pfd->pd_mtx);
	pfd->pd_bytes_fetched += BP_GET_LSIZE(bp);
	cv_broadcast(&pfd->pd_cv);
	mutex_exit(&pfd->pd_mtx);

	(void) arc_read(NULL, spa, bp, NULL, NULL, ZIO_PRIORITY_ASYNC_READ,
	    ZIO_FLAG_CANFAIL | ZIO_FLAG_SPECULATIVE, &aflags, zb);

	return (0);
}