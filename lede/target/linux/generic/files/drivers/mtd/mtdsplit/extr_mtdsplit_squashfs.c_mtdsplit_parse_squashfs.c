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
struct mtd_partition {scalar_t__ offset; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {scalar_t__ size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ROOTFS_SPLIT_NAME ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_get_squashfs_len (struct mtd_info*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mtd_rounddown_to_eb (scalar_t__,struct mtd_info*) ; 
 scalar_t__ mtd_roundup_to_eb (size_t,struct mtd_info*) ; 
 struct mtd_info* mtdpart_get_master (struct mtd_info*) ; 
 size_t mtdpart_get_offset (struct mtd_info*) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtdsplit_parse_squashfs(struct mtd_info *master,
			const struct mtd_partition **pparts,
			struct mtd_part_parser_data *data)
{
	struct mtd_partition *part;
	struct mtd_info *parent_mtd;
	size_t part_offset;
	size_t squashfs_len;
	int err;

	err = mtd_get_squashfs_len(master, 0, &squashfs_len);
	if (err)
		return err;

	parent_mtd = mtdpart_get_master(master);
	part_offset = mtdpart_get_offset(master);

	part = kzalloc(sizeof(*part), GFP_KERNEL);
	if (!part) {
		pr_alert("unable to allocate memory for \"%s\" partition\n",
			 ROOTFS_SPLIT_NAME);
		return -ENOMEM;
	}

	part->name = ROOTFS_SPLIT_NAME;
	part->offset = mtd_roundup_to_eb(part_offset + squashfs_len,
					 parent_mtd) - part_offset;
	part->size = mtd_rounddown_to_eb(master->size - part->offset, master);

	*pparts = part;
	return 1;
}