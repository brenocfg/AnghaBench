#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_4__ {int ncached_max; } ;
typedef  TYPE_1__ cache_bin_info_t ;
struct TYPE_5__ {int nregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 unsigned int NBINS ; 
 int SMALL_MAXCLASS ; 
 int TCACHE_NSLOTS_LARGE ; 
 int TCACHE_NSLOTS_SMALL_MAX ; 
 int TCACHE_NSLOTS_SMALL_MIN ; 
 int /*<<< orphan*/  WITNESS_RANK_TCACHES ; 
 int ZU (int) ; 
 int /*<<< orphan*/  b0get () ; 
 scalar_t__ base_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* bin_infos ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 
 int nhbins ; 
 int opt_lg_tcache_max ; 
 scalar_t__ stack_nelms ; 
 int sz_size2index (int) ; 
 TYPE_1__* tcache_bin_info ; 
 int tcache_maxclass ; 
 int /*<<< orphan*/  tcaches_mtx ; 

bool
tcache_boot(tsdn_t *tsdn) {
	/* If necessary, clamp opt_lg_tcache_max. */
	if (opt_lg_tcache_max < 0 || (ZU(1) << opt_lg_tcache_max) <
	    SMALL_MAXCLASS) {
		tcache_maxclass = SMALL_MAXCLASS;
	} else {
		tcache_maxclass = (ZU(1) << opt_lg_tcache_max);
	}

	if (malloc_mutex_init(&tcaches_mtx, "tcaches", WITNESS_RANK_TCACHES,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}

	nhbins = sz_size2index(tcache_maxclass) + 1;

	/* Initialize tcache_bin_info. */
	tcache_bin_info = (cache_bin_info_t *)base_alloc(tsdn, b0get(), nhbins
	    * sizeof(cache_bin_info_t), CACHELINE);
	if (tcache_bin_info == NULL) {
		return true;
	}
	stack_nelms = 0;
	unsigned i;
	for (i = 0; i < NBINS; i++) {
		if ((bin_infos[i].nregs << 1) <= TCACHE_NSLOTS_SMALL_MIN) {
			tcache_bin_info[i].ncached_max =
			    TCACHE_NSLOTS_SMALL_MIN;
		} else if ((bin_infos[i].nregs << 1) <=
		    TCACHE_NSLOTS_SMALL_MAX) {
			tcache_bin_info[i].ncached_max =
			    (bin_infos[i].nregs << 1);
		} else {
			tcache_bin_info[i].ncached_max =
			    TCACHE_NSLOTS_SMALL_MAX;
		}
		stack_nelms += tcache_bin_info[i].ncached_max;
	}
	for (; i < nhbins; i++) {
		tcache_bin_info[i].ncached_max = TCACHE_NSLOTS_LARGE;
		stack_nelms += tcache_bin_info[i].ncached_max;
	}

	return false;
}