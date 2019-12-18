#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_uint64_t ;
struct TYPE_5__ {int references; int ncounters; int /*<<< orphan*/  lock; struct TYPE_5__* copiedcounters; struct TYPE_5__* counters; int /*<<< orphan*/  magic; int /*<<< orphan*/ * mctx; int /*<<< orphan*/  counterlock; } ;
typedef  TYPE_1__ isc_stats_t ;
typedef  int /*<<< orphan*/  isc_stat_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_STATS_MAGIC ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_mem_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* isc_mem_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static isc_result_t
create_stats(isc_mem_t *mctx, int ncounters, isc_stats_t **statsp) {
	isc_stats_t *stats;
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(statsp != NULL && *statsp == NULL);

	stats = isc_mem_get(mctx, sizeof(*stats));
	if (stats == NULL)
		return (ISC_R_NOMEMORY);

	result = isc_mutex_init(&stats->lock);
	if (result != ISC_R_SUCCESS)
		goto clean_stats;

	stats->counters = isc_mem_get(mctx, sizeof(isc_stat_t) * ncounters);
	if (stats->counters == NULL) {
		result = ISC_R_NOMEMORY;
		goto clean_mutex;
	}
	stats->copiedcounters = isc_mem_get(mctx,
					    sizeof(isc_uint64_t) * ncounters);
	if (stats->copiedcounters == NULL) {
		result = ISC_R_NOMEMORY;
		goto clean_counters;
	}

#ifdef ISC_RWLOCK_USEATOMIC
	result = isc_rwlock_init(&stats->counterlock, 0, 0);
	if (result != ISC_R_SUCCESS)
		goto clean_copiedcounters;
#endif

	stats->references = 1;
	memset(stats->counters, 0, sizeof(isc_stat_t) * ncounters);
	stats->mctx = NULL;
	isc_mem_attach(mctx, &stats->mctx);
	stats->ncounters = ncounters;
	stats->magic = ISC_STATS_MAGIC;

	*statsp = stats;

	return (result);

clean_counters:
	isc_mem_put(mctx, stats->counters, sizeof(isc_stat_t) * ncounters);

#ifdef ISC_RWLOCK_USEATOMIC
clean_copiedcounters:
	isc_mem_put(mctx, stats->copiedcounters,
		    sizeof(isc_stat_t) * ncounters);
#endif

clean_mutex:
	DESTROYLOCK(&stats->lock);

clean_stats:
	isc_mem_put(mctx, stats, sizeof(*stats));

	return (result);
}