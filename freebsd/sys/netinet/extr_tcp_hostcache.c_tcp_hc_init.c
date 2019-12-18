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
typedef  void* u_int ;
struct hc_metrics {int dummy; } ;
struct hc_head {int /*<<< orphan*/  hch_mtx; scalar_t__ hch_length; int /*<<< orphan*/  hch_bucket; } ;
struct TYPE_2__ {int hashsize; int bucket_limit; int prune; int hashmask; int cache_limit; int /*<<< orphan*/  zone; struct hc_head* hashbase; int /*<<< orphan*/  expire; scalar_t__ cache_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_HOSTCACHE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int TCP_HOSTCACHE_BUCKETLIMIT ; 
 int /*<<< orphan*/  TCP_HOSTCACHE_EXPIRE ; 
 void* TCP_HOSTCACHE_HASHSIZE ; 
 int TCP_HOSTCACHE_PRUNE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  V_tcp_hc_callout ; 
 TYPE_1__ V_tcp_hostcache ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 int hz ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tcp_hc_purge ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,void*) ; 

void
tcp_hc_init(void)
{
	u_int cache_limit;
	int i;

	/*
	 * Initialize hostcache structures.
	 */
	V_tcp_hostcache.cache_count = 0;
	V_tcp_hostcache.hashsize = TCP_HOSTCACHE_HASHSIZE;
	V_tcp_hostcache.bucket_limit = TCP_HOSTCACHE_BUCKETLIMIT;
	V_tcp_hostcache.expire = TCP_HOSTCACHE_EXPIRE;
	V_tcp_hostcache.prune = TCP_HOSTCACHE_PRUNE;

	TUNABLE_INT_FETCH("net.inet.tcp.hostcache.hashsize",
	    &V_tcp_hostcache.hashsize);
	if (!powerof2(V_tcp_hostcache.hashsize)) {
		printf("WARNING: hostcache hash size is not a power of 2.\n");
		V_tcp_hostcache.hashsize = TCP_HOSTCACHE_HASHSIZE; /* default */
	}
	V_tcp_hostcache.hashmask = V_tcp_hostcache.hashsize - 1;

	TUNABLE_INT_FETCH("net.inet.tcp.hostcache.bucketlimit",
	    &V_tcp_hostcache.bucket_limit);

	cache_limit = V_tcp_hostcache.hashsize * V_tcp_hostcache.bucket_limit;
	V_tcp_hostcache.cache_limit = cache_limit;
	TUNABLE_INT_FETCH("net.inet.tcp.hostcache.cachelimit",
	    &V_tcp_hostcache.cache_limit);
	if (V_tcp_hostcache.cache_limit > cache_limit)
		V_tcp_hostcache.cache_limit = cache_limit;

	/*
	 * Allocate the hash table.
	 */
	V_tcp_hostcache.hashbase = (struct hc_head *)
	    malloc(V_tcp_hostcache.hashsize * sizeof(struct hc_head),
		   M_HOSTCACHE, M_WAITOK | M_ZERO);

	/*
	 * Initialize the hash buckets.
	 */
	for (i = 0; i < V_tcp_hostcache.hashsize; i++) {
		TAILQ_INIT(&V_tcp_hostcache.hashbase[i].hch_bucket);
		V_tcp_hostcache.hashbase[i].hch_length = 0;
		mtx_init(&V_tcp_hostcache.hashbase[i].hch_mtx, "tcp_hc_entry",
			  NULL, MTX_DEF);
	}

	/*
	 * Allocate the hostcache entries.
	 */
	V_tcp_hostcache.zone =
	    uma_zcreate("hostcache", sizeof(struct hc_metrics),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, 0);
	uma_zone_set_max(V_tcp_hostcache.zone, V_tcp_hostcache.cache_limit);

	/*
	 * Set up periodic cache cleanup.
	 */
	callout_init(&V_tcp_hc_callout, 1);
	callout_reset(&V_tcp_hc_callout, V_tcp_hostcache.prune * hz,
	    tcp_hc_purge, curvnet);
}