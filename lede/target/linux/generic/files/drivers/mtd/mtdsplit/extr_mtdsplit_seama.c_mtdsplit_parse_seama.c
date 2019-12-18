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
struct seama_header {int /*<<< orphan*/  metasize; int /*<<< orphan*/  size; int /*<<< orphan*/  magic; } ;
struct mtd_partition {int offset; size_t size; int /*<<< orphan*/  name; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {size_t size; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  enum mtdsplit_part_type { ____Placeholder_mtdsplit_part_type } mtdsplit_part_type ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERNEL_PART_NAME ; 
 int MTDSPLIT_PART_TYPE_UBI ; 
 int /*<<< orphan*/  ROOTFS_PART_NAME ; 
 size_t SEAMA_MAGIC ; 
 int /*<<< orphan*/  SEAMA_MIN_ROOTFS_OFFS ; 
 int SEAMA_NR_PARTS ; 
 int /*<<< orphan*/  UBI_PART_NAME ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_check_rootfs_magic (struct mtd_info*,size_t,int*) ; 
 int mtd_find_rootfs_from (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,int*) ; 
 int mtd_read (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,void*) ; 

__attribute__((used)) static int mtdsplit_parse_seama(struct mtd_info *master,
				const struct mtd_partition **pparts,
				struct mtd_part_parser_data *data)
{
	struct seama_header hdr;
	size_t hdr_len, retlen, kernel_ent_size;
	size_t rootfs_offset;
	struct mtd_partition *parts;
	enum mtdsplit_part_type type;
	int err;

	hdr_len = sizeof(hdr);
	err = mtd_read(master, 0, hdr_len, &retlen, (void *) &hdr);
	if (err)
		return err;

	if (retlen != hdr_len)
		return -EIO;

	/* sanity checks */
	if (be32_to_cpu(hdr.magic) != SEAMA_MAGIC)
		return -EINVAL;

	kernel_ent_size = hdr_len + be32_to_cpu(hdr.size) +
			  be16_to_cpu(hdr.metasize);
	if (kernel_ent_size > master->size)
		return -EINVAL;

	/* Check for the rootfs right after Seama entity with a kernel. */
	err = mtd_check_rootfs_magic(master, kernel_ent_size, &type);
	if (!err) {
		rootfs_offset = kernel_ent_size;
	} else {
		/*
		 * On some devices firmware entity might contain both: kernel
		 * and rootfs. We can't determine kernel size so we just have to
		 * look for rootfs magic.
		 * Start the search from an arbitrary offset.
		 */
		err = mtd_find_rootfs_from(master, SEAMA_MIN_ROOTFS_OFFS,
					   master->size, &rootfs_offset, &type);
		if (err)
			return err;
	}

	parts = kzalloc(SEAMA_NR_PARTS * sizeof(*parts), GFP_KERNEL);
	if (!parts)
		return -ENOMEM;

	parts[0].name = KERNEL_PART_NAME;
	parts[0].offset = sizeof hdr + be16_to_cpu(hdr.metasize);
	parts[0].size = rootfs_offset - parts[0].offset;

	if (type == MTDSPLIT_PART_TYPE_UBI)
		parts[1].name = UBI_PART_NAME;
	else
		parts[1].name = ROOTFS_PART_NAME;
	parts[1].offset = rootfs_offset;
	parts[1].size = master->size - rootfs_offset;

	*pparts = parts;
	return SEAMA_NR_PARTS;
}