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
struct namecache {int dummy; } ;
struct namecache_ts {struct namecache nc_nc; } ;

/* Variables and functions */
 int CACHE_PATH_CUTOFF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  cache_zone_large ; 
 int /*<<< orphan*/  cache_zone_large_ts ; 
 int /*<<< orphan*/  cache_zone_small ; 
 int /*<<< orphan*/  cache_zone_small_ts ; 
 void* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct namecache *
cache_alloc(int len, int ts)
{
	struct namecache_ts *ncp_ts;
	struct namecache *ncp;

	if (__predict_false(ts)) {
		if (len <= CACHE_PATH_CUTOFF)
			ncp_ts = uma_zalloc(cache_zone_small_ts, M_WAITOK);
		else
			ncp_ts = uma_zalloc(cache_zone_large_ts, M_WAITOK);
		ncp = &ncp_ts->nc_nc;
	} else {
		if (len <= CACHE_PATH_CUTOFF)
			ncp = uma_zalloc(cache_zone_small, M_WAITOK);
		else
			ncp = uma_zalloc(cache_zone_large, M_WAITOK);
	}
	return (ncp);
}