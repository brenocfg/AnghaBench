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
typedef  int /*<<< orphan*/  u32 ;
struct zram {int /*<<< orphan*/  mem_pool; int /*<<< orphan*/  comp; } ;
struct zcomp_strm {int dummy; } ;
struct page {int dummy; } ;
struct bio_vec {unsigned int bv_len; scalar_t__ bv_offset; struct page* bv_page; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  ZRAM_SAME ; 
 int /*<<< orphan*/  ZRAM_WB ; 
 int /*<<< orphan*/  ZS_MM_RO ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int read_from_bdev (struct zram*,struct bio_vec*,unsigned long,struct bio*,int) ; 
 scalar_t__ unlikely (int) ; 
 int zcomp_decompress (struct zcomp_strm*,void*,unsigned int,void*) ; 
 struct zcomp_strm* zcomp_stream_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcomp_stream_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_fill_page (void*,unsigned int,unsigned long) ; 
 unsigned long zram_get_element (struct zram*,int /*<<< orphan*/ ) ; 
 unsigned long zram_get_handle (struct zram*,int /*<<< orphan*/ ) ; 
 unsigned int zram_get_obj_size (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_slot_lock (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_slot_unlock (struct zram*,int /*<<< orphan*/ ) ; 
 scalar_t__ zram_test_flag (struct zram*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* zs_map_object (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zs_unmap_object (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int __zram_bvec_read(struct zram *zram, struct page *page, u32 index,
				struct bio *bio, bool partial_io)
{
	int ret;
	unsigned long handle;
	unsigned int size;
	void *src, *dst;

	zram_slot_lock(zram, index);
	if (zram_test_flag(zram, index, ZRAM_WB)) {
		struct bio_vec bvec;

		zram_slot_unlock(zram, index);

		bvec.bv_page = page;
		bvec.bv_len = PAGE_SIZE;
		bvec.bv_offset = 0;
		return read_from_bdev(zram, &bvec,
				zram_get_element(zram, index),
				bio, partial_io);
	}

	handle = zram_get_handle(zram, index);
	if (!handle || zram_test_flag(zram, index, ZRAM_SAME)) {
		unsigned long value;
		void *mem;

		value = handle ? zram_get_element(zram, index) : 0;
		mem = kmap_atomic(page);
		zram_fill_page(mem, PAGE_SIZE, value);
		kunmap_atomic(mem);
		zram_slot_unlock(zram, index);
		return 0;
	}

	size = zram_get_obj_size(zram, index);

	src = zs_map_object(zram->mem_pool, handle, ZS_MM_RO);
	if (size == PAGE_SIZE) {
		dst = kmap_atomic(page);
		memcpy(dst, src, PAGE_SIZE);
		kunmap_atomic(dst);
		ret = 0;
	} else {
		struct zcomp_strm *zstrm = zcomp_stream_get(zram->comp);

		dst = kmap_atomic(page);
		ret = zcomp_decompress(zstrm, src, size, dst);
		kunmap_atomic(dst);
		zcomp_stream_put(zram->comp);
	}
	zs_unmap_object(zram->mem_pool, handle);
	zram_slot_unlock(zram, index);

	/* Should NEVER happen. Return bio error if it does. */
	if (unlikely(ret))
		pr_err("Decompression failed! err=%d, page=%u\n", ret, index);

	return ret;
}