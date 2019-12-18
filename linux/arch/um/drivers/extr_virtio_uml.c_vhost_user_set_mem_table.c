#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtio_uml_device {int dummy; } ;
struct TYPE_5__ {int num; int /*<<< orphan*/ * regions; } ;
struct TYPE_6__ {TYPE_2__ mem_regions; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  request; } ;
struct vhost_user_msg {TYPE_3__ payload; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_USER_SET_MEM_TABLE ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_iomem ; 
 scalar_t__ highmem ; 
 scalar_t__ physmem_size ; 
 unsigned long uml_physmem ; 
 unsigned long uml_reserved ; 
 int vhost_user_init_mem_region (unsigned long,scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int vhost_user_send (struct virtio_uml_device*,int,struct vhost_user_msg*,int*,int) ; 

__attribute__((used)) static int vhost_user_set_mem_table(struct virtio_uml_device *vu_dev)
{
	struct vhost_user_msg msg = {
		.header.request = VHOST_USER_SET_MEM_TABLE,
		.header.size = sizeof(msg.payload.mem_regions),
		.payload.mem_regions.num = 1,
	};
	unsigned long reserved = uml_reserved - uml_physmem;
	int fds[2];
	int rc;

	/*
	 * This is a bit tricky, see also the comment with setup_physmem().
	 *
	 * Essentially, setup_physmem() uses a file to mmap() our physmem,
	 * but the code and data we *already* have is omitted. To us, this
	 * is no difference, since they both become part of our address
	 * space and memory consumption. To somebody looking in from the
	 * outside, however, it is different because the part of our memory
	 * consumption that's already part of the binary (code/data) is not
	 * mapped from the file, so it's not visible to another mmap from
	 * the file descriptor.
	 *
	 * Thus, don't advertise this space to the vhost-user slave. This
	 * means that the slave will likely abort or similar when we give
	 * it an address from the hidden range, since it's not marked as
	 * a valid address, but at least that way we detect the issue and
	 * don't just have the slave read an all-zeroes buffer from the
	 * shared memory file, or write something there that we can never
	 * see (depending on the direction of the virtqueue traffic.)
	 *
	 * Since we usually don't want to use .text for virtio buffers,
	 * this effectively means that you cannot use
	 *  1) global variables, which are in the .bss and not in the shm
	 *     file-backed memory
	 *  2) the stack in some processes, depending on where they have
	 *     their stack (or maybe only no interrupt stack?)
	 *
	 * The stack is already not typically valid for DMA, so this isn't
	 * much of a restriction, but global variables might be encountered.
	 *
	 * It might be possible to fix it by copying around the data that's
	 * between bss_start and where we map the file now, but it's not
	 * something that you typically encounter with virtio drivers, so
	 * it didn't seem worthwhile.
	 */
	rc = vhost_user_init_mem_region(reserved, physmem_size - reserved,
					&fds[0],
					&msg.payload.mem_regions.regions[0]);

	if (rc < 0)
		return rc;
	if (highmem) {
		msg.payload.mem_regions.num++;
		rc = vhost_user_init_mem_region(__pa(end_iomem), highmem,
				&fds[1], &msg.payload.mem_regions.regions[1]);
		if (rc < 0)
			return rc;
	}

	return vhost_user_send(vu_dev, false, &msg, fds,
			       msg.payload.mem_regions.num);
}