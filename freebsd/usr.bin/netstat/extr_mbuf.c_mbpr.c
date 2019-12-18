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
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  u_long ;
struct sfstat {scalar_t__ sf_allocwait; scalar_t__ sf_allocfail; scalar_t__ sf_busy; scalar_t__ sf_rhpages_read; scalar_t__ sf_rhpages_requested; scalar_t__ sf_pages_bogus; scalar_t__ sf_pages_valid; scalar_t__ sf_pages_read; scalar_t__ sf_iocnt; scalar_t__ sf_noiocnt; scalar_t__ sf_syscalls; } ;
struct memory_type_list {int dummy; } ;
struct memory_type {int dummy; } ;
typedef  int /*<<< orphan*/  sfstat ;
typedef  int /*<<< orphan*/  nsfbufs ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCATOR_MALLOC ; 
 int /*<<< orphan*/  ALLOCATOR_UMA ; 
 int /*<<< orphan*/  MBUF_CLUSTER_MEM_NAME ; 
 int /*<<< orphan*/  MBUF_JUMBO16_MEM_NAME ; 
 int /*<<< orphan*/  MBUF_JUMBO9_MEM_NAME ; 
 int /*<<< orphan*/  MBUF_JUMBOP_MEM_NAME ; 
 int /*<<< orphan*/  MBUF_MEM_NAME ; 
 int /*<<< orphan*/  MBUF_PACKET_MEM_NAME ; 
 int /*<<< orphan*/  MBUF_TAG_MEM_NAME ; 
 int MEMSTAT_ERROR_KVM ; 
 scalar_t__ fetch_stats (char*,int /*<<< orphan*/ ,struct sfstat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kread_counters ; 
 int /*<<< orphan*/  kvm_geterr (void*) ; 
 scalar_t__ live ; 
 int memstat_get_bytes (struct memory_type*) ; 
 int memstat_get_count (struct memory_type*) ; 
 int memstat_get_countlimit (struct memory_type*) ; 
 int memstat_get_failures (struct memory_type*) ; 
 int memstat_get_free (struct memory_type*) ; 
 int memstat_get_size (struct memory_type*) ; 
 int memstat_get_sleeps (struct memory_type*) ; 
 scalar_t__ memstat_kvm_all (struct memory_type_list*,void*) ; 
 struct memory_type_list* memstat_mtl_alloc () ; 
 struct memory_type* memstat_mtl_find (struct memory_type_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstat_mtl_free (struct memory_type_list*) ; 
 int memstat_mtl_geterror (struct memory_type_list*) ; 
 int /*<<< orphan*/  memstat_strerror (int) ; 
 scalar_t__ memstat_sysctl_all (struct memory_type_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tag_count ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,int,...) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

void
mbpr(void *kvmd, u_long mbaddr)
{
	struct memory_type_list *mtlp;
	struct memory_type *mtp;
	uintmax_t mbuf_count, mbuf_bytes, mbuf_free, mbuf_failures, mbuf_size;
	uintmax_t mbuf_sleeps;
	uintmax_t cluster_count, cluster_limit, cluster_free;
	uintmax_t cluster_failures, cluster_size, cluster_sleeps;
	uintmax_t packet_count, packet_bytes, packet_free, packet_failures;
	uintmax_t packet_sleeps;
	uintmax_t tag_bytes;
	uintmax_t jumbop_count, jumbop_limit, jumbop_free;
	uintmax_t jumbop_failures, jumbop_sleeps, jumbop_size;
	uintmax_t jumbo9_count, jumbo9_limit, jumbo9_free;
	uintmax_t jumbo9_failures, jumbo9_sleeps, jumbo9_size;
	uintmax_t jumbo16_count, jumbo16_limit, jumbo16_free;
	uintmax_t jumbo16_failures, jumbo16_sleeps, jumbo16_size;
	uintmax_t bytes_inuse, bytes_incache, bytes_total;
	int nsfbufs, nsfbufspeak, nsfbufsused;
	struct sfstat sfstat;
	size_t mlen;
	int error;

	mtlp = memstat_mtl_alloc();
	if (mtlp == NULL) {
		xo_warn("memstat_mtl_alloc");
		return;
	}

	/*
	 * Use memstat_*_all() because some mbuf-related memory is in uma(9),
	 * and some malloc(9).
	 */
	if (live) {
		if (memstat_sysctl_all(mtlp, 0) < 0) {
			xo_warnx("memstat_sysctl_all: %s",
			    memstat_strerror(memstat_mtl_geterror(mtlp)));
			goto out;
		}
	} else {
		if (memstat_kvm_all(mtlp, kvmd) < 0) {
			error = memstat_mtl_geterror(mtlp);
			if (error == MEMSTAT_ERROR_KVM)
				xo_warnx("memstat_kvm_all: %s",
				    kvm_geterr(kvmd));
			else
				xo_warnx("memstat_kvm_all: %s",
				    memstat_strerror(error));
			goto out;
		}
	}

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_UMA, MBUF_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: zone %s not found", MBUF_MEM_NAME);
		goto out;
	}
	mbuf_count = memstat_get_count(mtp);
	mbuf_bytes = memstat_get_bytes(mtp);
	mbuf_free = memstat_get_free(mtp);
	mbuf_failures = memstat_get_failures(mtp);
	mbuf_sleeps = memstat_get_sleeps(mtp);
	mbuf_size = memstat_get_size(mtp);

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_UMA, MBUF_PACKET_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: zone %s not found",
		    MBUF_PACKET_MEM_NAME);
		goto out;
	}
	packet_count = memstat_get_count(mtp);
	packet_bytes = memstat_get_bytes(mtp);
	packet_free = memstat_get_free(mtp);
	packet_sleeps = memstat_get_sleeps(mtp);
	packet_failures = memstat_get_failures(mtp);

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_UMA, MBUF_CLUSTER_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: zone %s not found",
		    MBUF_CLUSTER_MEM_NAME);
		goto out;
	}
	cluster_count = memstat_get_count(mtp);
	cluster_limit = memstat_get_countlimit(mtp);
	cluster_free = memstat_get_free(mtp);
	cluster_failures = memstat_get_failures(mtp);
	cluster_sleeps = memstat_get_sleeps(mtp);
	cluster_size = memstat_get_size(mtp);

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_MALLOC, MBUF_TAG_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: malloc type %s not found",
		    MBUF_TAG_MEM_NAME);
		goto out;
	}
	tag_bytes = memstat_get_bytes(mtp);

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_UMA, MBUF_JUMBOP_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: zone %s not found",
		    MBUF_JUMBOP_MEM_NAME);
		goto out;
	}
	jumbop_count = memstat_get_count(mtp);
	jumbop_limit = memstat_get_countlimit(mtp);
	jumbop_free = memstat_get_free(mtp);
	jumbop_failures = memstat_get_failures(mtp);
	jumbop_sleeps = memstat_get_sleeps(mtp);
	jumbop_size = memstat_get_size(mtp);

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_UMA, MBUF_JUMBO9_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: zone %s not found",
		    MBUF_JUMBO9_MEM_NAME);
		goto out;
	}
	jumbo9_count = memstat_get_count(mtp);
	jumbo9_limit = memstat_get_countlimit(mtp);
	jumbo9_free = memstat_get_free(mtp);
	jumbo9_failures = memstat_get_failures(mtp);
	jumbo9_sleeps = memstat_get_sleeps(mtp);
	jumbo9_size = memstat_get_size(mtp);

	mtp = memstat_mtl_find(mtlp, ALLOCATOR_UMA, MBUF_JUMBO16_MEM_NAME);
	if (mtp == NULL) {
		xo_warnx("memstat_mtl_find: zone %s not found",
		    MBUF_JUMBO16_MEM_NAME);
		goto out;
	}
	jumbo16_count = memstat_get_count(mtp);
	jumbo16_limit = memstat_get_countlimit(mtp);
	jumbo16_free = memstat_get_free(mtp);
	jumbo16_failures = memstat_get_failures(mtp);
	jumbo16_sleeps = memstat_get_sleeps(mtp);
	jumbo16_size = memstat_get_size(mtp);

	xo_open_container("mbuf-statistics");

	xo_emit("{:mbuf-current/%ju}/{:mbuf-cache/%ju}/{:mbuf-total/%ju} "
	    "{N:mbufs in use (current\\/cache\\/total)}\n",
	    mbuf_count + packet_count, mbuf_free + packet_free,
	    mbuf_count + packet_count + mbuf_free + packet_free);

	xo_emit("{:cluster-current/%ju}/{:cluster-cache/%ju}/"
	    "{:cluster-total/%ju}/{:cluster-max/%ju} "
	    "{N:mbuf clusters in use (current\\/cache\\/total\\/max)}\n",
	    cluster_count - packet_free, cluster_free + packet_free,
	    cluster_count + cluster_free, cluster_limit);

	xo_emit("{:packet-count/%ju}/{:packet-free/%ju} "
	    "{N:mbuf+clusters out of packet secondary zone in use "
	    "(current\\/cache)}\n",
	    packet_count, packet_free);

	xo_emit("{:jumbo-count/%ju}/{:jumbo-cache/%ju}/{:jumbo-total/%ju}/"
	    "{:jumbo-max/%ju} {:jumbo-page-size/%ju}{U:k} {N:(page size)} "
	    "{N:jumbo clusters in use (current\\/cache\\/total\\/max)}\n",
	    jumbop_count, jumbop_free, jumbop_count + jumbop_free,
	    jumbop_limit, jumbop_size / 1024);

	xo_emit("{:jumbo9-count/%ju}/{:jumbo9-cache/%ju}/"
	    "{:jumbo9-total/%ju}/{:jumbo9-max/%ju} "
	    "{N:9k jumbo clusters in use (current\\/cache\\/total\\/max)}\n",
	    jumbo9_count, jumbo9_free, jumbo9_count + jumbo9_free,
	    jumbo9_limit);

	xo_emit("{:jumbo16-count/%ju}/{:jumbo16-cache/%ju}/"
	    "{:jumbo16-total/%ju}/{:jumbo16-limit/%ju} "
	    "{N:16k jumbo clusters in use (current\\/cache\\/total\\/max)}\n",
	    jumbo16_count, jumbo16_free, jumbo16_count + jumbo16_free,
	    jumbo16_limit);

#if 0
	xo_emit("{:tag-count/%ju} {N:mbuf tags in use}\n", tag_count);
#endif

	/*-
	 * Calculate in-use bytes as:
	 * - straight mbuf memory
	 * - mbuf memory in packets
	 * - the clusters attached to packets
	 * - and the rest of the non-packet-attached clusters.
	 * - m_tag memory
	 * This avoids counting the clusters attached to packets in the cache.
	 * This currently excludes sf_buf space.
	 */
	bytes_inuse =
	    mbuf_bytes +			/* straight mbuf memory */
	    packet_bytes +			/* mbufs in packets */
	    (packet_count * cluster_size) +	/* clusters in packets */
	    /* other clusters */
	    ((cluster_count - packet_count - packet_free) * cluster_size) +
	    tag_bytes +
	    (jumbop_count * jumbop_size) +	/* jumbo clusters */
	    (jumbo9_count * jumbo9_size) +
	    (jumbo16_count * jumbo16_size);

	/*
	 * Calculate in-cache bytes as:
	 * - cached straught mbufs
	 * - cached packet mbufs
	 * - cached packet clusters
	 * - cached straight clusters
	 * This currently excludes sf_buf space.
	 */
	bytes_incache =
	    (mbuf_free * mbuf_size) +		/* straight free mbufs */
	    (packet_free * mbuf_size) +		/* mbufs in free packets */
	    (packet_free * cluster_size) +	/* clusters in free packets */
	    (cluster_free * cluster_size) +	/* free clusters */
	    (jumbop_free * jumbop_size) +	/* jumbo clusters */
	    (jumbo9_free * jumbo9_size) +
	    (jumbo16_free * jumbo16_size);

	/*
	 * Total is bytes in use + bytes in cache.  This doesn't take into
	 * account various other misc data structures, overhead, etc, but
	 * gives the user something useful despite that.
	 */
	bytes_total = bytes_inuse + bytes_incache;

	xo_emit("{:bytes-in-use/%ju}{U:K}/{:bytes-in-cache/%ju}{U:K}/"
	    "{:bytes-total/%ju}{U:K} "
	    "{N:bytes allocated to network (current\\/cache\\/total)}\n",
	    bytes_inuse / 1024, bytes_incache / 1024, bytes_total / 1024);

	xo_emit("{:mbuf-failures/%ju}/{:cluster-failures/%ju}/"
	    "{:packet-failures/%ju} {N:requests for mbufs denied "
	    "(mbufs\\/clusters\\/mbuf+clusters)}\n",
	    mbuf_failures, cluster_failures, packet_failures);
	xo_emit("{:mbuf-sleeps/%ju}/{:cluster-sleeps/%ju}/{:packet-sleeps/%ju} "
	    "{N:requests for mbufs delayed "
	    "(mbufs\\/clusters\\/mbuf+clusters)}\n",
	    mbuf_sleeps, cluster_sleeps, packet_sleeps);

	xo_emit("{:jumbop-sleeps/%ju}/{:jumbo9-sleeps/%ju}/"
	    "{:jumbo16-sleeps/%ju} {N:/requests for jumbo clusters delayed "
	    "(%juk\\/9k\\/16k)}\n",
	    jumbop_sleeps, jumbo9_sleeps, jumbo16_sleeps, jumbop_size / 1024);
	xo_emit("{:jumbop-failures/%ju}/{:jumbo9-failures/%ju}/"
	    "{:jumbo16-failures/%ju} {N:/requests for jumbo clusters denied "
	    "(%juk\\/9k\\/16k)}\n",
	    jumbop_failures, jumbo9_failures, jumbo16_failures,
	    jumbop_size / 1024);

	mlen = sizeof(nsfbufs);
	if (live &&
	    sysctlbyname("kern.ipc.nsfbufs", &nsfbufs, &mlen, NULL, 0) == 0 &&
	    sysctlbyname("kern.ipc.nsfbufsused", &nsfbufsused, &mlen,
	    NULL, 0) == 0 &&
	    sysctlbyname("kern.ipc.nsfbufspeak", &nsfbufspeak, &mlen,
	    NULL, 0) == 0)
		xo_emit("{:nsfbufs-current/%d}/{:nsfbufs-peak/%d}/"
		    "{:nsfbufs/%d} "
		    "{N:sfbufs in use (current\\/peak\\/max)}\n",
		    nsfbufsused, nsfbufspeak, nsfbufs);

	if (fetch_stats("kern.ipc.sfstat", mbaddr, &sfstat, sizeof(sfstat),
	    kread_counters) != 0)
		goto out;

        xo_emit("{:sendfile-syscalls/%ju} {N:sendfile syscalls}\n",
	    (uintmax_t)sfstat.sf_syscalls); 
        xo_emit("{:sendfile-no-io/%ju} "
	    "{N:sendfile syscalls completed without I\\/O request}\n", 
            (uintmax_t)sfstat.sf_noiocnt);
	xo_emit("{:sendfile-io-count/%ju} "
	    "{N:requests for I\\/O initiated by sendfile}\n",
	    (uintmax_t)sfstat.sf_iocnt);
        xo_emit("{:sendfile-pages-sent/%ju} "
	    "{N:pages read by sendfile as part of a request}\n",
            (uintmax_t)sfstat.sf_pages_read);
        xo_emit("{:sendfile-pages-valid/%ju} "
	    "{N:pages were valid at time of a sendfile request}\n",
            (uintmax_t)sfstat.sf_pages_valid);
        xo_emit("{:sendfile-pages-bogus/%ju} "
	    "{N:pages were valid and substituted to bogus page}\n",
            (uintmax_t)sfstat.sf_pages_bogus);
        xo_emit("{:sendfile-requested-readahead/%ju} "
	    "{N:pages were requested for read ahead by applications}\n",
            (uintmax_t)sfstat.sf_rhpages_requested);
        xo_emit("{:sendfile-readahead/%ju} "
	    "{N:pages were read ahead by sendfile}\n",
            (uintmax_t)sfstat.sf_rhpages_read);
	xo_emit("{:sendfile-busy-encounters/%ju} "
	    "{N:times sendfile encountered an already busy page}\n",
	    (uintmax_t)sfstat.sf_busy);
	xo_emit("{:sfbufs-alloc-failed/%ju} {N:requests for sfbufs denied}\n",
	    (uintmax_t)sfstat.sf_allocfail);
	xo_emit("{:sfbufs-alloc-wait/%ju} {N:requests for sfbufs delayed}\n",
	    (uintmax_t)sfstat.sf_allocwait);
out:
	xo_close_container("mbuf-statistics");
	memstat_mtl_free(mtlp);
}