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
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int BKVASIZE ; 
 long INT_MAX ; 
 int LONG_MAX ; 
 long MAXPHYS ; 
 scalar_t__ NSWBUF_MIN ; 
 int PAGE_SIZE ; 
 long TRANSIENT_DENOM ; 
 int bio_transient_maxcnt ; 
 void* buf ; 
 int maxbcache ; 
 int /*<<< orphan*/  maxbcachebuf_adjust () ; 
 scalar_t__ min (int,int) ; 
 int nbuf ; 
 scalar_t__ nswbuf ; 
 int /*<<< orphan*/  printf (char*,int,long) ; 
 scalar_t__ unmapped_buf_allowed ; 

caddr_t
kern_vfs_bio_buffer_alloc(caddr_t v, long physmem_est)
{
	int tuned_nbuf;
	long maxbuf, maxbuf_sz, buf_sz,	biotmap_sz;

	/*
	 * physmem_est is in pages.  Convert it to kilobytes (assumes
	 * PAGE_SIZE is >= 1K)
	 */
	physmem_est = physmem_est * (PAGE_SIZE / 1024);

	maxbcachebuf_adjust();
	/*
	 * The nominal buffer size (and minimum KVA allocation) is BKVASIZE.
	 * For the first 64MB of ram nominally allocate sufficient buffers to
	 * cover 1/4 of our ram.  Beyond the first 64MB allocate additional
	 * buffers to cover 1/10 of our ram over 64MB.  When auto-sizing
	 * the buffer cache we limit the eventual kva reservation to
	 * maxbcache bytes.
	 *
	 * factor represents the 1/4 x ram conversion.
	 */
	if (nbuf == 0) {
		int factor = 4 * BKVASIZE / 1024;

		nbuf = 50;
		if (physmem_est > 4096)
			nbuf += min((physmem_est - 4096) / factor,
			    65536 / factor);
		if (physmem_est > 65536)
			nbuf += min((physmem_est - 65536) * 2 / (factor * 5),
			    32 * 1024 * 1024 / (factor * 5));

		if (maxbcache && nbuf > maxbcache / BKVASIZE)
			nbuf = maxbcache / BKVASIZE;
		tuned_nbuf = 1;
	} else
		tuned_nbuf = 0;

	/* XXX Avoid unsigned long overflows later on with maxbufspace. */
	maxbuf = (LONG_MAX / 3) / BKVASIZE;
	if (nbuf > maxbuf) {
		if (!tuned_nbuf)
			printf("Warning: nbufs lowered from %d to %ld\n", nbuf,
			    maxbuf);
		nbuf = maxbuf;
	}

	/*
	 * Ideal allocation size for the transient bio submap is 10%
	 * of the maximal space buffer map.  This roughly corresponds
	 * to the amount of the buffer mapped for typical UFS load.
	 *
	 * Clip the buffer map to reserve space for the transient
	 * BIOs, if its extent is bigger than 90% (80% on i386) of the
	 * maximum buffer map extent on the platform.
	 *
	 * The fall-back to the maxbuf in case of maxbcache unset,
	 * allows to not trim the buffer KVA for the architectures
	 * with ample KVA space.
	 */
	if (bio_transient_maxcnt == 0 && unmapped_buf_allowed) {
		maxbuf_sz = maxbcache != 0 ? maxbcache : maxbuf * BKVASIZE;
		buf_sz = (long)nbuf * BKVASIZE;
		if (buf_sz < maxbuf_sz / TRANSIENT_DENOM *
		    (TRANSIENT_DENOM - 1)) {
			/*
			 * There is more KVA than memory.  Do not
			 * adjust buffer map size, and assign the rest
			 * of maxbuf to transient map.
			 */
			biotmap_sz = maxbuf_sz - buf_sz;
		} else {
			/*
			 * Buffer map spans all KVA we could afford on
			 * this platform.  Give 10% (20% on i386) of
			 * the buffer map to the transient bio map.
			 */
			biotmap_sz = buf_sz / TRANSIENT_DENOM;
			buf_sz -= biotmap_sz;
		}
		if (biotmap_sz / INT_MAX > MAXPHYS)
			bio_transient_maxcnt = INT_MAX;
		else
			bio_transient_maxcnt = biotmap_sz / MAXPHYS;
		/*
		 * Artificially limit to 1024 simultaneous in-flight I/Os
		 * using the transient mapping.
		 */
		if (bio_transient_maxcnt > 1024)
			bio_transient_maxcnt = 1024;
		if (tuned_nbuf)
			nbuf = buf_sz / BKVASIZE;
	}

	if (nswbuf == 0) {
		nswbuf = min(nbuf / 4, 256);
		if (nswbuf < NSWBUF_MIN)
			nswbuf = NSWBUF_MIN;
	}

	/*
	 * Reserve space for the buffer cache buffers
	 */
	buf = (void *)v;
	v = (caddr_t)(buf + nbuf);

	return(v);
}