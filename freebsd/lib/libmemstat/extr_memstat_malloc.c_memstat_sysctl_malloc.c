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
struct memory_type_list {void* mtl_error; int /*<<< orphan*/  mtl_list; } ;
struct memory_type {scalar_t__ mt_numfrees; scalar_t__ mt_numallocs; scalar_t__ mt_count; scalar_t__ mt_memfreed; scalar_t__ mt_memalloced; scalar_t__ mt_bytes; TYPE_1__* mt_percpu_alloc; int /*<<< orphan*/  mt_sizemask; } ;
struct malloc_type_stream_header {scalar_t__ mtsh_version; int mtsh_maxcpus; int mtsh_count; } ;
struct malloc_type_stats {int /*<<< orphan*/  mts_size; scalar_t__ mts_numfrees; scalar_t__ mts_numallocs; scalar_t__ mts_memfreed; scalar_t__ mts_memalloced; } ;
struct malloc_type_header {int /*<<< orphan*/  mth_name; } ;
typedef  int /*<<< orphan*/  maxcpus ;
typedef  int /*<<< orphan*/  count ;
struct TYPE_2__ {int /*<<< orphan*/  mtp_sizemask; scalar_t__ mtp_numfrees; scalar_t__ mtp_numallocs; scalar_t__ mtp_memfreed; scalar_t__ mtp_memalloced; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCATOR_MALLOC ; 
 scalar_t__ EACCES ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ EPERM ; 
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ MALLOC_TYPE_STREAM_VERSION ; 
 void* MEMSTAT_ERROR_DATAERROR ; 
 void* MEMSTAT_ERROR_NOMEMORY ; 
 void* MEMSTAT_ERROR_PERMISSION ; 
 void* MEMSTAT_ERROR_VERSION ; 
 struct memory_type* _memstat_mt_allocate (struct memory_type_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _memstat_mt_reset_stats (struct memory_type*,int) ; 
 int /*<<< orphan*/  _memstat_mtl_empty (struct memory_type_list*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 struct memory_type* memstat_mtl_find (struct memory_type_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,...) ; 

int
memstat_sysctl_malloc(struct memory_type_list *list, int flags)
{
	struct malloc_type_stream_header *mtshp;
	struct malloc_type_header *mthp;
	struct malloc_type_stats *mtsp;
	struct memory_type *mtp;
	int count, hint_dontsearch, i, j, maxcpus;
	char *buffer, *p;
	size_t size;

	hint_dontsearch = LIST_EMPTY(&list->mtl_list);

	/*
	 * Query the number of CPUs, number of malloc types so that we can
	 * guess an initial buffer size.  We loop until we succeed or really
	 * fail.  Note that the value of maxcpus we query using sysctl is not
	 * the version we use when processing the real data -- that is read
	 * from the header.
	 */
retry:
	size = sizeof(maxcpus);
	if (sysctlbyname("kern.smp.maxcpus", &maxcpus, &size, NULL, 0) < 0) {
		if (errno == EACCES || errno == EPERM)
			list->mtl_error = MEMSTAT_ERROR_PERMISSION;
		else
			list->mtl_error = MEMSTAT_ERROR_DATAERROR;
		return (-1);
	}
	if (size != sizeof(maxcpus)) {
		list->mtl_error = MEMSTAT_ERROR_DATAERROR;
		return (-1);
	}

	size = sizeof(count);
	if (sysctlbyname("kern.malloc_count", &count, &size, NULL, 0) < 0) {
		if (errno == EACCES || errno == EPERM)
			list->mtl_error = MEMSTAT_ERROR_PERMISSION;
		else
			list->mtl_error = MEMSTAT_ERROR_VERSION;
		return (-1);
	}
	if (size != sizeof(count)) {
		list->mtl_error = MEMSTAT_ERROR_DATAERROR;
		return (-1);
	}

	size = sizeof(*mthp) + count * (sizeof(*mthp) + sizeof(*mtsp) *
	    maxcpus);

	buffer = malloc(size);
	if (buffer == NULL) {
		list->mtl_error = MEMSTAT_ERROR_NOMEMORY;
		return (-1);
	}

	if (sysctlbyname("kern.malloc_stats", buffer, &size, NULL, 0) < 0) {
		/*
		 * XXXRW: ENOMEM is an ambiguous return, we should bound the
		 * number of loops, perhaps.
		 */
		if (errno == ENOMEM) {
			free(buffer);
			goto retry;
		}
		if (errno == EACCES || errno == EPERM)
			list->mtl_error = MEMSTAT_ERROR_PERMISSION;
		else
			list->mtl_error = MEMSTAT_ERROR_VERSION;
		free(buffer);
		return (-1);
	}

	if (size == 0) {
		free(buffer);
		return (0);
	}

	if (size < sizeof(*mtshp)) {
		list->mtl_error = MEMSTAT_ERROR_VERSION;
		free(buffer);
		return (-1);
	}
	p = buffer;
	mtshp = (struct malloc_type_stream_header *)p;
	p += sizeof(*mtshp);

	if (mtshp->mtsh_version != MALLOC_TYPE_STREAM_VERSION) {
		list->mtl_error = MEMSTAT_ERROR_VERSION;
		free(buffer);
		return (-1);
	}

	/*
	 * For the remainder of this function, we are quite trusting about
	 * the layout of structures and sizes, since we've determined we have
	 * a matching version and acceptable CPU count.
	 */
	maxcpus = mtshp->mtsh_maxcpus;
	count = mtshp->mtsh_count;
	for (i = 0; i < count; i++) {
		mthp = (struct malloc_type_header *)p;
		p += sizeof(*mthp);

		if (hint_dontsearch == 0) {
			mtp = memstat_mtl_find(list, ALLOCATOR_MALLOC,
			    mthp->mth_name);
		} else
			mtp = NULL;
		if (mtp == NULL)
			mtp = _memstat_mt_allocate(list, ALLOCATOR_MALLOC,
			    mthp->mth_name, maxcpus);
		if (mtp == NULL) {
			_memstat_mtl_empty(list);
			free(buffer);
			list->mtl_error = MEMSTAT_ERROR_NOMEMORY;
			return (-1);
		}

		/*
		 * Reset the statistics on a current node.
		 */
		_memstat_mt_reset_stats(mtp, maxcpus);

		for (j = 0; j < maxcpus; j++) {
			mtsp = (struct malloc_type_stats *)p;
			p += sizeof(*mtsp);

			/*
			 * Sumarize raw statistics across CPUs into coalesced
			 * statistics.
			 */
			mtp->mt_memalloced += mtsp->mts_memalloced;
			mtp->mt_memfreed += mtsp->mts_memfreed;
			mtp->mt_numallocs += mtsp->mts_numallocs;
			mtp->mt_numfrees += mtsp->mts_numfrees;
			mtp->mt_sizemask |= mtsp->mts_size;

			/*
			 * Copies of per-CPU statistics.
			 */
			mtp->mt_percpu_alloc[j].mtp_memalloced =
			    mtsp->mts_memalloced;
			mtp->mt_percpu_alloc[j].mtp_memfreed =
			    mtsp->mts_memfreed;
			mtp->mt_percpu_alloc[j].mtp_numallocs =
			    mtsp->mts_numallocs;
			mtp->mt_percpu_alloc[j].mtp_numfrees =
			    mtsp->mts_numfrees;
			mtp->mt_percpu_alloc[j].mtp_sizemask =
			    mtsp->mts_size;
		}

		/*
		 * Derived cross-CPU statistics.
		 */
		mtp->mt_bytes = mtp->mt_memalloced - mtp->mt_memfreed;
		mtp->mt_count = mtp->mt_numallocs - mtp->mt_numfrees;
	}

	free(buffer);

	return (0);
}