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
struct one_flush_context {struct issue_flush_context* ctx; struct drbd_device* device; } ;
struct issue_flush_context {int /*<<< orphan*/  pending; int /*<<< orphan*/  error; } ;
struct drbd_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  flush_jif; TYPE_1__* ldev; int /*<<< orphan*/  kref; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_end_io; struct one_flush_context* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  backing_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FLUSH_PENDING ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_OP_FLUSH ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_destroy_device ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct one_flush_context*) ; 
 struct one_flush_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one_flush_endio ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void submit_one_flush(struct drbd_device *device, struct issue_flush_context *ctx)
{
	struct bio *bio = bio_alloc(GFP_NOIO, 0);
	struct one_flush_context *octx = kmalloc(sizeof(*octx), GFP_NOIO);
	if (!bio || !octx) {
		drbd_warn(device, "Could not allocate a bio, CANNOT ISSUE FLUSH\n");
		/* FIXME: what else can I do now?  disconnecting or detaching
		 * really does not help to improve the state of the world, either.
		 */
		kfree(octx);
		if (bio)
			bio_put(bio);

		ctx->error = -ENOMEM;
		put_ldev(device);
		kref_put(&device->kref, drbd_destroy_device);
		return;
	}

	octx->device = device;
	octx->ctx = ctx;
	bio_set_dev(bio, device->ldev->backing_bdev);
	bio->bi_private = octx;
	bio->bi_end_io = one_flush_endio;
	bio->bi_opf = REQ_OP_FLUSH | REQ_PREFLUSH;

	device->flush_jif = jiffies;
	set_bit(FLUSH_PENDING, &device->flags);
	atomic_inc(&ctx->pending);
	submit_bio(bio);
}