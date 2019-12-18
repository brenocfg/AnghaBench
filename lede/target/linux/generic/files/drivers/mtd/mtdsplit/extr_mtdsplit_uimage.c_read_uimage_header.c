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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int mtd_read (struct mtd_info*,size_t,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_uimage_header(struct mtd_info *mtd, size_t offset, u_char *buf,
		   size_t header_len)
{
	size_t retlen;
	int ret;

	ret = mtd_read(mtd, offset, header_len, &retlen, buf);
	if (ret) {
		pr_debug("read error in \"%s\"\n", mtd->name);
		return ret;
	}

	if (retlen != header_len) {
		pr_debug("short read in \"%s\"\n", mtd->name);
		return -EIO;
	}

	return 0;
}