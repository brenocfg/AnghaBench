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
struct bufdomain {int bd_freebuffers; int bd_hifreebuffers; int bd_lofreebuffers; int bd_maxbufspace; int bd_hibufspace; int bd_lobufspace; int bd_bufspacethresh; int bd_hidirtybuffers; int bd_lodirtybuffers; int bd_dirtybufthresh; int bd_lim; scalar_t__ bd_numdirtybuffers; scalar_t__ bd_bufspace; } ;
struct buf {int b_domain; int /*<<< orphan*/  b_dep; scalar_t__ b_kvabase; scalar_t__ b_data; scalar_t__ b_xflags; scalar_t__ b_subqueue; int /*<<< orphan*/  b_qindex; void* b_wcred; void* b_rcred; int /*<<< orphan*/  b_flags; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 long BKVASIZE ; 
 int BUF_DOMAINS ; 
 int /*<<< orphan*/  BUF_LOCKINIT (struct buf*) ; 
 int /*<<< orphan*/  B_INVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MAXBSIZE ; 
 int /*<<< orphan*/  MAXPHYS ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 void* NOCRED ; 
 int /*<<< orphan*/  QUEUE_EMPTY ; 
 int /*<<< orphan*/  QUEUE_NONE ; 
 int /*<<< orphan*/  bd_init (struct bufdomain*) ; 
 int /*<<< orphan*/  bdirtylock ; 
 int /*<<< orphan*/  bdlock ; 
 struct bufdomain* bdomain ; 
 int /*<<< orphan*/  bq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  bq_insert (int /*<<< orphan*/ *,struct buf*,int) ; 
 int /*<<< orphan*/  bqempty ; 
 struct buf* buf ; 
 int buf_domains ; 
 int /*<<< orphan*/  buf_import ; 
 int /*<<< orphan*/  buf_release ; 
 int /*<<< orphan*/  buf_zone ; 
 void* bufdefragcnt ; 
 int /*<<< orphan*/  buffer_arena ; 
 void* buffreekvacnt ; 
 int /*<<< orphan*/  bufkva_reclaim ; 
 void* bufkvaspace ; 
 int bufspacethresh ; 
 int /*<<< orphan*/  bzero (struct buf*,int) ; 
 void* counter_u64_alloc (int /*<<< orphan*/ ) ; 
 int dirtybufthresh ; 
 void* getnewbufcalls ; 
 void* getnewbufrestarts ; 
 int hibufspace ; 
 int hidirtybuffers ; 
 int hifreebuffers ; 
 int hirunningspace ; 
 int howmany (int,int) ; 
 scalar_t__ kva_alloc (int /*<<< orphan*/ ) ; 
 int lmax (int,int) ; 
 int lmin (int /*<<< orphan*/ ,int) ; 
 int lobufspace ; 
 int lodirtybuffers ; 
 int lofreebuffers ; 
 int /*<<< orphan*/  lorunningspace ; 
 void* mappingrestarts ; 
 int maxbcachebuf ; 
 int maxbufmallocspace ; 
 int maxbufspace ; 
 scalar_t__ mp_maxid ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nbuf ; 
 void* notbufdflushes ; 
 void* numbufallocfails ; 
 int numfreebuffers ; 
 int /*<<< orphan*/  rbreqlock ; 
 int /*<<< orphan*/  roundup (int,int) ; 
 int /*<<< orphan*/  uma_zcache_create (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unmapped_buf ; 
 int /*<<< orphan*/  vmem_set_reclaim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bufinit(void)
{
	struct buf *bp;
	int i;

	KASSERT(maxbcachebuf >= MAXBSIZE,
	    ("maxbcachebuf (%d) must be >= MAXBSIZE (%d)\n", maxbcachebuf,
	    MAXBSIZE));
	bq_init(&bqempty, QUEUE_EMPTY, -1, "bufq empty lock");
	mtx_init(&rbreqlock, "runningbufspace lock", NULL, MTX_DEF);
	mtx_init(&bdlock, "buffer daemon lock", NULL, MTX_DEF);
	mtx_init(&bdirtylock, "dirty buf lock", NULL, MTX_DEF);

	unmapped_buf = (caddr_t)kva_alloc(MAXPHYS);

	/* finally, initialize each buffer header and stick on empty q */
	for (i = 0; i < nbuf; i++) {
		bp = &buf[i];
		bzero(bp, sizeof *bp);
		bp->b_flags = B_INVAL;
		bp->b_rcred = NOCRED;
		bp->b_wcred = NOCRED;
		bp->b_qindex = QUEUE_NONE;
		bp->b_domain = -1;
		bp->b_subqueue = mp_maxid + 1;
		bp->b_xflags = 0;
		bp->b_data = bp->b_kvabase = unmapped_buf;
		LIST_INIT(&bp->b_dep);
		BUF_LOCKINIT(bp);
		bq_insert(&bqempty, bp, false);
	}

	/*
	 * maxbufspace is the absolute maximum amount of buffer space we are 
	 * allowed to reserve in KVM and in real terms.  The absolute maximum
	 * is nominally used by metadata.  hibufspace is the nominal maximum
	 * used by most other requests.  The differential is required to 
	 * ensure that metadata deadlocks don't occur.
	 *
	 * maxbufspace is based on BKVASIZE.  Allocating buffers larger then
	 * this may result in KVM fragmentation which is not handled optimally
	 * by the system. XXX This is less true with vmem.  We could use
	 * PAGE_SIZE.
	 */
	maxbufspace = (long)nbuf * BKVASIZE;
	hibufspace = lmax(3 * maxbufspace / 4, maxbufspace - maxbcachebuf * 10);
	lobufspace = (hibufspace / 20) * 19; /* 95% */
	bufspacethresh = lobufspace + (hibufspace - lobufspace) / 2;

	/*
	 * Note: The 16 MiB upper limit for hirunningspace was chosen
	 * arbitrarily and may need further tuning. It corresponds to
	 * 128 outstanding write IO requests (if IO size is 128 KiB),
	 * which fits with many RAID controllers' tagged queuing limits.
	 * The lower 1 MiB limit is the historical upper limit for
	 * hirunningspace.
	 */
	hirunningspace = lmax(lmin(roundup(hibufspace / 64, maxbcachebuf),
	    16 * 1024 * 1024), 1024 * 1024);
	lorunningspace = roundup((hirunningspace * 2) / 3, maxbcachebuf);

	/*
	 * Limit the amount of malloc memory since it is wired permanently into
	 * the kernel space.  Even though this is accounted for in the buffer
	 * allocation, we don't want the malloced region to grow uncontrolled.
	 * The malloc scheme improves memory utilization significantly on
	 * average (small) directories.
	 */
	maxbufmallocspace = hibufspace / 20;

	/*
	 * Reduce the chance of a deadlock occurring by limiting the number
	 * of delayed-write dirty buffers we allow to stack up.
	 */
	hidirtybuffers = nbuf / 4 + 20;
	dirtybufthresh = hidirtybuffers * 9 / 10;
	/*
	 * To support extreme low-memory systems, make sure hidirtybuffers
	 * cannot eat up all available buffer space.  This occurs when our
	 * minimum cannot be met.  We try to size hidirtybuffers to 3/4 our
	 * buffer space assuming BKVASIZE'd buffers.
	 */
	while ((long)hidirtybuffers * BKVASIZE > 3 * hibufspace / 4) {
		hidirtybuffers >>= 1;
	}
	lodirtybuffers = hidirtybuffers / 2;

	/*
	 * lofreebuffers should be sufficient to avoid stalling waiting on
	 * buf headers under heavy utilization.  The bufs in per-cpu caches
	 * are counted as free but will be unavailable to threads executing
	 * on other cpus.
	 *
	 * hifreebuffers is the free target for the bufspace daemon.  This
	 * should be set appropriately to limit work per-iteration.
	 */
	lofreebuffers = MIN((nbuf / 25) + (20 * mp_ncpus), 128 * mp_ncpus);
	hifreebuffers = (3 * lofreebuffers) / 2;
	numfreebuffers = nbuf;

	/* Setup the kva and free list allocators. */
	vmem_set_reclaim(buffer_arena, bufkva_reclaim);
	buf_zone = uma_zcache_create("buf free cache", sizeof(struct buf),
	    NULL, NULL, NULL, NULL, buf_import, buf_release, NULL, 0);

	/*
	 * Size the clean queue according to the amount of buffer space.
	 * One queue per-256mb up to the max.  More queues gives better
	 * concurrency but less accurate LRU.
	 */
	buf_domains = MIN(howmany(maxbufspace, 256*1024*1024), BUF_DOMAINS);
	for (i = 0 ; i < buf_domains; i++) {
		struct bufdomain *bd;

		bd = &bdomain[i];
		bd_init(bd);
		bd->bd_freebuffers = nbuf / buf_domains;
		bd->bd_hifreebuffers = hifreebuffers / buf_domains;
		bd->bd_lofreebuffers = lofreebuffers / buf_domains;
		bd->bd_bufspace = 0;
		bd->bd_maxbufspace = maxbufspace / buf_domains;
		bd->bd_hibufspace = hibufspace / buf_domains;
		bd->bd_lobufspace = lobufspace / buf_domains;
		bd->bd_bufspacethresh = bufspacethresh / buf_domains;
		bd->bd_numdirtybuffers = 0;
		bd->bd_hidirtybuffers = hidirtybuffers / buf_domains;
		bd->bd_lodirtybuffers = lodirtybuffers / buf_domains;
		bd->bd_dirtybufthresh = dirtybufthresh / buf_domains;
		/* Don't allow more than 2% of bufs in the per-cpu caches. */
		bd->bd_lim = nbuf / buf_domains / 50 / mp_ncpus;
	}
	getnewbufcalls = counter_u64_alloc(M_WAITOK);
	getnewbufrestarts = counter_u64_alloc(M_WAITOK);
	mappingrestarts = counter_u64_alloc(M_WAITOK);
	numbufallocfails = counter_u64_alloc(M_WAITOK);
	notbufdflushes = counter_u64_alloc(M_WAITOK);
	buffreekvacnt = counter_u64_alloc(M_WAITOK);
	bufdefragcnt = counter_u64_alloc(M_WAITOK);
	bufkvaspace = counter_u64_alloc(M_WAITOK);
}