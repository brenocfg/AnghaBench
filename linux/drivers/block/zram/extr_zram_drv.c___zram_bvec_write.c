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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pages_stored; int /*<<< orphan*/  huge_pages; int /*<<< orphan*/  compr_data_size; int /*<<< orphan*/  writestall; int /*<<< orphan*/  same_pages; } ;
struct zram {unsigned long limit_pages; TYPE_1__ stats; int /*<<< orphan*/  mem_pool; int /*<<< orphan*/  comp; } ;
struct zcomp_strm {void* buffer; } ;
struct page {int dummy; } ;
struct bio_vec {struct page* bv_page; } ;
struct bio {int dummy; } ;
typedef  enum zram_pageflags { ____Placeholder_zram_pageflags } zram_pageflags ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_NOIO ; 
 unsigned int PAGE_SIZE ; 
 int ZRAM_HUGE ; 
 int ZRAM_SAME ; 
 int /*<<< orphan*/  ZS_MM_WO ; 
 int __GFP_HIGHMEM ; 
 int __GFP_KSWAPD_RECLAIM ; 
 int __GFP_MOVABLE ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic64_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 unsigned int huge_class_size ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 scalar_t__ page_same_filled (void*,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_used_max (struct zram*,unsigned long) ; 
 int zcomp_compress (struct zcomp_strm*,void*,unsigned int*) ; 
 struct zcomp_strm* zcomp_stream_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcomp_stream_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_free_page (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_set_element (struct zram*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  zram_set_flag (struct zram*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zram_set_handle (struct zram*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  zram_set_obj_size (struct zram*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  zram_slot_lock (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_slot_unlock (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zs_free (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long zs_get_total_pages (int /*<<< orphan*/ ) ; 
 unsigned long zs_malloc (int /*<<< orphan*/ ,unsigned int,int) ; 
 void* zs_map_object (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zs_unmap_object (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int __zram_bvec_write(struct zram *zram, struct bio_vec *bvec,
				u32 index, struct bio *bio)
{
	int ret = 0;
	unsigned long alloced_pages;
	unsigned long handle = 0;
	unsigned int comp_len = 0;
	void *src, *dst, *mem;
	struct zcomp_strm *zstrm;
	struct page *page = bvec->bv_page;
	unsigned long element = 0;
	enum zram_pageflags flags = 0;

	mem = kmap_atomic(page);
	if (page_same_filled(mem, &element)) {
		kunmap_atomic(mem);
		/* Free memory associated with this sector now. */
		flags = ZRAM_SAME;
		atomic64_inc(&zram->stats.same_pages);
		goto out;
	}
	kunmap_atomic(mem);

compress_again:
	zstrm = zcomp_stream_get(zram->comp);
	src = kmap_atomic(page);
	ret = zcomp_compress(zstrm, src, &comp_len);
	kunmap_atomic(src);

	if (unlikely(ret)) {
		zcomp_stream_put(zram->comp);
		pr_err("Compression failed! err=%d\n", ret);
		zs_free(zram->mem_pool, handle);
		return ret;
	}

	if (comp_len >= huge_class_size)
		comp_len = PAGE_SIZE;
	/*
	 * handle allocation has 2 paths:
	 * a) fast path is executed with preemption disabled (for
	 *  per-cpu streams) and has __GFP_DIRECT_RECLAIM bit clear,
	 *  since we can't sleep;
	 * b) slow path enables preemption and attempts to allocate
	 *  the page with __GFP_DIRECT_RECLAIM bit set. we have to
	 *  put per-cpu compression stream and, thus, to re-do
	 *  the compression once handle is allocated.
	 *
	 * if we have a 'non-null' handle here then we are coming
	 * from the slow path and handle has already been allocated.
	 */
	if (!handle)
		handle = zs_malloc(zram->mem_pool, comp_len,
				__GFP_KSWAPD_RECLAIM |
				__GFP_NOWARN |
				__GFP_HIGHMEM |
				__GFP_MOVABLE);
	if (!handle) {
		zcomp_stream_put(zram->comp);
		atomic64_inc(&zram->stats.writestall);
		handle = zs_malloc(zram->mem_pool, comp_len,
				GFP_NOIO | __GFP_HIGHMEM |
				__GFP_MOVABLE);
		if (handle)
			goto compress_again;
		return -ENOMEM;
	}

	alloced_pages = zs_get_total_pages(zram->mem_pool);
	update_used_max(zram, alloced_pages);

	if (zram->limit_pages && alloced_pages > zram->limit_pages) {
		zcomp_stream_put(zram->comp);
		zs_free(zram->mem_pool, handle);
		return -ENOMEM;
	}

	dst = zs_map_object(zram->mem_pool, handle, ZS_MM_WO);

	src = zstrm->buffer;
	if (comp_len == PAGE_SIZE)
		src = kmap_atomic(page);
	memcpy(dst, src, comp_len);
	if (comp_len == PAGE_SIZE)
		kunmap_atomic(src);

	zcomp_stream_put(zram->comp);
	zs_unmap_object(zram->mem_pool, handle);
	atomic64_add(comp_len, &zram->stats.compr_data_size);
out:
	/*
	 * Free memory associated with this sector
	 * before overwriting unused sectors.
	 */
	zram_slot_lock(zram, index);
	zram_free_page(zram, index);

	if (comp_len == PAGE_SIZE) {
		zram_set_flag(zram, index, ZRAM_HUGE);
		atomic64_inc(&zram->stats.huge_pages);
	}

	if (flags) {
		zram_set_flag(zram, index, flags);
		zram_set_element(zram, index, element);
	}  else {
		zram_set_handle(zram, index, handle);
		zram_set_obj_size(zram, index, comp_len);
	}
	zram_slot_unlock(zram, index);

	/* Update stats */
	atomic64_inc(&zram->stats.pages_stored);
	return ret;
}