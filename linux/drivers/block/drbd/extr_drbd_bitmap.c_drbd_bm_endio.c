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
struct drbd_device {int /*<<< orphan*/  misc_wait; struct drbd_bitmap* bitmap; } ;
struct drbd_bm_aio_ctx {int flags; int done; int /*<<< orphan*/  kref; int /*<<< orphan*/  in_flight; int /*<<< orphan*/  error; struct drbd_device* device; } ;
struct drbd_bitmap {int /*<<< orphan*/ * bm_pages; } ;
struct bio {TYPE_1__* bi_io_vec; scalar_t__ bi_status; struct drbd_bm_aio_ctx* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int BM_AIO_COPY_PAGES ; 
 scalar_t__ __ratelimit (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_first_page_all (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  bm_clear_page_io_err (int /*<<< orphan*/ ) ; 
 unsigned int bm_page_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_page_unlock_io (struct drbd_device*,unsigned int) ; 
 int /*<<< orphan*/  bm_set_page_io_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_test_page_unchanged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_bm_aio_ctx_destroy ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  drbd_md_io_page_pool ; 
 int /*<<< orphan*/  drbd_ratelimit_state ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dynamic_drbd_dbg (struct drbd_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_bm_endio(struct bio *bio)
{
	struct drbd_bm_aio_ctx *ctx = bio->bi_private;
	struct drbd_device *device = ctx->device;
	struct drbd_bitmap *b = device->bitmap;
	unsigned int idx = bm_page_to_idx(bio_first_page_all(bio));

	if ((ctx->flags & BM_AIO_COPY_PAGES) == 0 &&
	    !bm_test_page_unchanged(b->bm_pages[idx]))
		drbd_warn(device, "bitmap page idx %u changed during IO!\n", idx);

	if (bio->bi_status) {
		/* ctx error will hold the completed-last non-zero error code,
		 * in case error codes differ. */
		ctx->error = blk_status_to_errno(bio->bi_status);
		bm_set_page_io_err(b->bm_pages[idx]);
		/* Not identical to on disk version of it.
		 * Is BM_PAGE_IO_ERROR enough? */
		if (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "IO ERROR %d on bitmap page idx %u\n",
					bio->bi_status, idx);
	} else {
		bm_clear_page_io_err(b->bm_pages[idx]);
		dynamic_drbd_dbg(device, "bitmap page idx %u completed\n", idx);
	}

	bm_page_unlock_io(device, idx);

	if (ctx->flags & BM_AIO_COPY_PAGES)
		mempool_free(bio->bi_io_vec[0].bv_page, &drbd_md_io_page_pool);

	bio_put(bio);

	if (atomic_dec_and_test(&ctx->in_flight)) {
		ctx->done = 1;
		wake_up(&device->misc_wait);
		kref_put(&ctx->kref, &drbd_bm_aio_ctx_destroy);
	}
}