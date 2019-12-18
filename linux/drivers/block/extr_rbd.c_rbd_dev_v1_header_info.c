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
typedef  size_t u64 ;
typedef  int u32 ;
struct rbd_image_snap_ondisk {int dummy; } ;
struct rbd_image_header_ondisk {int /*<<< orphan*/  snap_count; int /*<<< orphan*/  snap_names_len; } ;
struct rbd_device {int /*<<< orphan*/  header_oloc; int /*<<< orphan*/  header_oid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct rbd_image_header_ondisk*) ; 
 struct rbd_image_header_ondisk* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_dev_ondisk_valid (struct rbd_image_header_ondisk*) ; 
 int rbd_header_from_disk (struct rbd_device*,struct rbd_image_header_ondisk*) ; 
 int rbd_obj_read_sync (struct rbd_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rbd_image_header_ondisk*,size_t) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,...) ; 

__attribute__((used)) static int rbd_dev_v1_header_info(struct rbd_device *rbd_dev)
{
	struct rbd_image_header_ondisk *ondisk = NULL;
	u32 snap_count = 0;
	u64 names_size = 0;
	u32 want_count;
	int ret;

	/*
	 * The complete header will include an array of its 64-bit
	 * snapshot ids, followed by the names of those snapshots as
	 * a contiguous block of NUL-terminated strings.  Note that
	 * the number of snapshots could change by the time we read
	 * it in, in which case we re-read it.
	 */
	do {
		size_t size;

		kfree(ondisk);

		size = sizeof (*ondisk);
		size += snap_count * sizeof (struct rbd_image_snap_ondisk);
		size += names_size;
		ondisk = kmalloc(size, GFP_KERNEL);
		if (!ondisk)
			return -ENOMEM;

		ret = rbd_obj_read_sync(rbd_dev, &rbd_dev->header_oid,
					&rbd_dev->header_oloc, ondisk, size);
		if (ret < 0)
			goto out;
		if ((size_t)ret < size) {
			ret = -ENXIO;
			rbd_warn(rbd_dev, "short header read (want %zd got %d)",
				size, ret);
			goto out;
		}
		if (!rbd_dev_ondisk_valid(ondisk)) {
			ret = -ENXIO;
			rbd_warn(rbd_dev, "invalid header");
			goto out;
		}

		names_size = le64_to_cpu(ondisk->snap_names_len);
		want_count = snap_count;
		snap_count = le32_to_cpu(ondisk->snap_count);
	} while (snap_count != want_count);

	ret = rbd_header_from_disk(rbd_dev, ondisk);
out:
	kfree(ondisk);

	return ret;
}