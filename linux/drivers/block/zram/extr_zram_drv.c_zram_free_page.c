#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pages_stored; int /*<<< orphan*/  compr_data_size; int /*<<< orphan*/  same_pages; int /*<<< orphan*/  huge_pages; } ;
struct zram {TYPE_2__* table; TYPE_1__ stats; int /*<<< orphan*/  mem_pool; } ;
struct TYPE_4__ {unsigned long flags; scalar_t__ ac_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned long) ; 
 int /*<<< orphan*/  ZRAM_HUGE ; 
 int /*<<< orphan*/  ZRAM_IDLE ; 
 unsigned long ZRAM_LOCK ; 
 int /*<<< orphan*/  ZRAM_SAME ; 
 unsigned long ZRAM_UNDER_WB ; 
 int /*<<< orphan*/  ZRAM_WB ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_block_bdev (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_clear_flag (struct zram*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_get_element (struct zram*,size_t) ; 
 unsigned long zram_get_handle (struct zram*,size_t) ; 
 int /*<<< orphan*/  zram_get_obj_size (struct zram*,size_t) ; 
 int /*<<< orphan*/  zram_set_handle (struct zram*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_set_obj_size (struct zram*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ zram_test_flag (struct zram*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zs_free (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void zram_free_page(struct zram *zram, size_t index)
{
	unsigned long handle;

#ifdef CONFIG_ZRAM_MEMORY_TRACKING
	zram->table[index].ac_time = 0;
#endif
	if (zram_test_flag(zram, index, ZRAM_IDLE))
		zram_clear_flag(zram, index, ZRAM_IDLE);

	if (zram_test_flag(zram, index, ZRAM_HUGE)) {
		zram_clear_flag(zram, index, ZRAM_HUGE);
		atomic64_dec(&zram->stats.huge_pages);
	}

	if (zram_test_flag(zram, index, ZRAM_WB)) {
		zram_clear_flag(zram, index, ZRAM_WB);
		free_block_bdev(zram, zram_get_element(zram, index));
		goto out;
	}

	/*
	 * No memory is allocated for same element filled pages.
	 * Simply clear same page flag.
	 */
	if (zram_test_flag(zram, index, ZRAM_SAME)) {
		zram_clear_flag(zram, index, ZRAM_SAME);
		atomic64_dec(&zram->stats.same_pages);
		goto out;
	}

	handle = zram_get_handle(zram, index);
	if (!handle)
		return;

	zs_free(zram->mem_pool, handle);

	atomic64_sub(zram_get_obj_size(zram, index),
			&zram->stats.compr_data_size);
out:
	atomic64_dec(&zram->stats.pages_stored);
	zram_set_handle(zram, index, 0);
	zram_set_obj_size(zram, index, 0);
	WARN_ON_ONCE(zram->table[index].flags &
		~(1UL << ZRAM_LOCK | 1UL << ZRAM_UNDER_WB));
}