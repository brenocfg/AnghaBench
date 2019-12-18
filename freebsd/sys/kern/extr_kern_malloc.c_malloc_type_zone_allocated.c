#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct malloc_type_stats {unsigned long mts_memalloced; int mts_size; int /*<<< orphan*/  mts_numallocs; } ;
struct malloc_type_internal {scalar_t__* mti_probes; int /*<<< orphan*/  mti_stats; } ;
struct malloc_type {struct malloc_type_internal* ks_handle; } ;
typedef  int /*<<< orphan*/  dtrace_malloc_probe ;

/* Variables and functions */
 size_t DTMALLOC_PROBE_MALLOC ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  dtrace_malloc_enabled ; 
 struct malloc_type_stats* zpcpu_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
malloc_type_zone_allocated(struct malloc_type *mtp, unsigned long size,
    int zindx)
{
	struct malloc_type_internal *mtip;
	struct malloc_type_stats *mtsp;

	critical_enter();
	mtip = mtp->ks_handle;
	mtsp = zpcpu_get(mtip->mti_stats);
	if (size > 0) {
		mtsp->mts_memalloced += size;
		mtsp->mts_numallocs++;
	}
	if (zindx != -1)
		mtsp->mts_size |= 1 << zindx;

#ifdef KDTRACE_HOOKS
	if (__predict_false(dtrace_malloc_enabled)) {
		uint32_t probe_id = mtip->mti_probes[DTMALLOC_PROBE_MALLOC];
		if (probe_id != 0)
			(dtrace_malloc_probe)(probe_id,
			    (uintptr_t) mtp, (uintptr_t) mtip,
			    (uintptr_t) mtsp, size, zindx);
	}
#endif

	critical_exit();
}