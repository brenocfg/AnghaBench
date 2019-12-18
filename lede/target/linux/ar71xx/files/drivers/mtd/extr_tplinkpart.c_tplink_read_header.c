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
typedef  size_t u32 ;
struct tplink_fw_header {int /*<<< orphan*/  kernel_ofs; int /*<<< orphan*/  version; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 size_t TPLINK_HEADER_V1 ; 
 size_t TPLINK_HEADER_V2 ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int mtd_read (struct mtd_info*,size_t,size_t,size_t*,unsigned char*) ; 
 int /*<<< orphan*/  vfree (struct tplink_fw_header*) ; 
 struct tplink_fw_header* vmalloc (int) ; 

__attribute__((used)) static struct tplink_fw_header *
tplink_read_header(struct mtd_info *mtd, size_t offset)
{
	struct tplink_fw_header *header;
	size_t header_len;
	size_t retlen;
	int ret;
	u32 t;

	header = vmalloc(sizeof(*header));
	if (!header)
		goto err;

	header_len = sizeof(struct tplink_fw_header);
	ret = mtd_read(mtd, offset, header_len, &retlen,
		       (unsigned char *) header);
	if (ret)
		goto err_free_header;

	if (retlen != header_len)
		goto err_free_header;

	/* sanity checks */
	t = be32_to_cpu(header->version);
	if ((t != TPLINK_HEADER_V1) && (t != TPLINK_HEADER_V2))
		goto err_free_header;

	t = be32_to_cpu(header->kernel_ofs);
	if (t != header_len)
		goto err_free_header;

	return header;

err_free_header:
	vfree(header);
err:
	return NULL;
}