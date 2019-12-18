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
typedef  long u64 ;
struct zs_pool_stats {int /*<<< orphan*/  pages_compacted; } ;
struct TYPE_2__ {int /*<<< orphan*/  huge_pages; int /*<<< orphan*/  same_pages; int /*<<< orphan*/  compr_data_size; int /*<<< orphan*/  max_used_pages; int /*<<< orphan*/  pages_stored; } ;
struct zram {long limit_pages; int /*<<< orphan*/  init_lock; TYPE_1__ stats; int /*<<< orphan*/  mem_pool; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 long atomic64_read (int /*<<< orphan*/ *) ; 
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ init_done (struct zram*) ; 
 int /*<<< orphan*/  memset (struct zs_pool_stats*,int,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,long,long,long,long,long,long,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 long zs_get_total_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zs_pool_stats (int /*<<< orphan*/ ,struct zs_pool_stats*) ; 

__attribute__((used)) static ssize_t mm_stat_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct zram *zram = dev_to_zram(dev);
	struct zs_pool_stats pool_stats;
	u64 orig_size, mem_used = 0;
	long max_used;
	ssize_t ret;

	memset(&pool_stats, 0x00, sizeof(struct zs_pool_stats));

	down_read(&zram->init_lock);
	if (init_done(zram)) {
		mem_used = zs_get_total_pages(zram->mem_pool);
		zs_pool_stats(zram->mem_pool, &pool_stats);
	}

	orig_size = atomic64_read(&zram->stats.pages_stored);
	max_used = atomic_long_read(&zram->stats.max_used_pages);

	ret = scnprintf(buf, PAGE_SIZE,
			"%8llu %8llu %8llu %8lu %8ld %8llu %8lu %8llu\n",
			orig_size << PAGE_SHIFT,
			(u64)atomic64_read(&zram->stats.compr_data_size),
			mem_used << PAGE_SHIFT,
			zram->limit_pages << PAGE_SHIFT,
			max_used << PAGE_SHIFT,
			(u64)atomic64_read(&zram->stats.same_pages),
			pool_stats.pages_compacted,
			(u64)atomic64_read(&zram->stats.huge_pages));
	up_read(&zram->init_lock);

	return ret;
}