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
typedef  int u64 ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int NOTIFY_STOP_MASK ; 
 int* cache_err_dcache ; 
 int /*<<< orphan*/  co_cache_error_chain ; 
 unsigned long cvmx_get_core_num () ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long long) ; 
 int raw_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long long read_c0_errorepc () ; 
 int read_octeon_c0_dcacheerr () ; 
 int read_octeon_c0_icacheerr () ; 
 int /*<<< orphan*/  write_octeon_c0_icacheerr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void co_cache_error_call_notifiers(unsigned long val)
{
	int rv = raw_notifier_call_chain(&co_cache_error_chain, val, NULL);
	if ((rv & ~NOTIFY_STOP_MASK) != NOTIFY_OK) {
		u64 dcache_err;
		unsigned long coreid = cvmx_get_core_num();
		u64 icache_err = read_octeon_c0_icacheerr();

		if (val) {
			dcache_err = cache_err_dcache[coreid];
			cache_err_dcache[coreid] = 0;
		} else {
			dcache_err = read_octeon_c0_dcacheerr();
		}

		pr_err("Core%lu: Cache error exception:\n", coreid);
		pr_err("cp0_errorepc == %lx\n", read_c0_errorepc());
		if (icache_err & 1) {
			pr_err("CacheErr (Icache) == %llx\n",
			       (unsigned long long)icache_err);
			write_octeon_c0_icacheerr(0);
		}
		if (dcache_err & 1) {
			pr_err("CacheErr (Dcache) == %llx\n",
			       (unsigned long long)dcache_err);
		}
	}
}