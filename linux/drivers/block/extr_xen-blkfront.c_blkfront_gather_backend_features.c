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
struct blkfront_info {int feature_flush; int feature_fua; int feature_persistent; unsigned int max_indirect_segments; TYPE_1__* xbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otherend; } ;

/* Variables and functions */
 unsigned int BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
 int HZ ; 
 int /*<<< orphan*/  blkfront_mutex ; 
 int /*<<< orphan*/  blkfront_setup_discard (struct blkfront_info*) ; 
 int /*<<< orphan*/  blkfront_work ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 unsigned int xen_blkif_max_segments ; 
 int xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blkfront_gather_backend_features(struct blkfront_info *info)
{
	unsigned int indirect_segments;

	info->feature_flush = 0;
	info->feature_fua = 0;

	/*
	 * If there's no "feature-barrier" defined, then it means
	 * we're dealing with a very old backend which writes
	 * synchronously; nothing to do.
	 *
	 * If there are barriers, then we use flush.
	 */
	if (xenbus_read_unsigned(info->xbdev->otherend, "feature-barrier", 0)) {
		info->feature_flush = 1;
		info->feature_fua = 1;
	}

	/*
	 * And if there is "feature-flush-cache" use that above
	 * barriers.
	 */
	if (xenbus_read_unsigned(info->xbdev->otherend, "feature-flush-cache",
				 0)) {
		info->feature_flush = 1;
		info->feature_fua = 0;
	}

	if (xenbus_read_unsigned(info->xbdev->otherend, "feature-discard", 0))
		blkfront_setup_discard(info);

	info->feature_persistent =
		!!xenbus_read_unsigned(info->xbdev->otherend,
				       "feature-persistent", 0);

	indirect_segments = xenbus_read_unsigned(info->xbdev->otherend,
					"feature-max-indirect-segments", 0);
	if (indirect_segments > xen_blkif_max_segments)
		indirect_segments = xen_blkif_max_segments;
	if (indirect_segments <= BLKIF_MAX_SEGMENTS_PER_REQUEST)
		indirect_segments = 0;
	info->max_indirect_segments = indirect_segments;

	if (info->feature_persistent) {
		mutex_lock(&blkfront_mutex);
		schedule_delayed_work(&blkfront_work, HZ * 10);
		mutex_unlock(&blkfront_mutex);
	}
}