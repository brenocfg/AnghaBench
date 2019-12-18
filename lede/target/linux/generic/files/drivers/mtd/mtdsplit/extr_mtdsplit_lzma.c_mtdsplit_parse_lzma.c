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
typedef  scalar_t__ u32 ;
struct mtd_partition {size_t offset; size_t size; int /*<<< orphan*/  name; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {size_t size; int /*<<< orphan*/  erasesize; } ;
struct lzma_header {int* props; int size_high; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERNEL_PART_NAME ; 
 int LZMA_NR_PARTS ; 
 int /*<<< orphan*/  ROOTFS_PART_NAME ; 
 scalar_t__ get_unaligned_le32 (int*) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_find_rootfs_from (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int mtd_read (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,void*) ; 

__attribute__((used)) static int mtdsplit_parse_lzma(struct mtd_info *master,
			       const struct mtd_partition **pparts,
			       struct mtd_part_parser_data *data)
{
	struct lzma_header hdr;
	size_t hdr_len, retlen;
	size_t rootfs_offset;
	u32 t;
	struct mtd_partition *parts;
	int err;

	hdr_len = sizeof(hdr);
	err = mtd_read(master, 0, hdr_len, &retlen, (void *) &hdr);
	if (err)
		return err;

	if (retlen != hdr_len)
		return -EIO;

	/* verify LZMA properties */
	if (hdr.props[0] >= (9 * 5 * 5))
		return -EINVAL;

	t = get_unaligned_le32(&hdr.props[1]);
	if (!is_power_of_2(t))
		return -EINVAL;

	t = get_unaligned_le32(&hdr.size_high);
	if (t)
		return -EINVAL;

	err = mtd_find_rootfs_from(master, master->erasesize, master->size,
				   &rootfs_offset, NULL);
	if (err)
		return err;

	parts = kzalloc(LZMA_NR_PARTS * sizeof(*parts), GFP_KERNEL);
	if (!parts)
		return -ENOMEM;

	parts[0].name = KERNEL_PART_NAME;
	parts[0].offset = 0;
	parts[0].size = rootfs_offset;

	parts[1].name = ROOTFS_PART_NAME;
	parts[1].offset = rootfs_offset;
	parts[1].size = master->size - rootfs_offset;

	*pparts = parts;
	return LZMA_NR_PARTS;
}