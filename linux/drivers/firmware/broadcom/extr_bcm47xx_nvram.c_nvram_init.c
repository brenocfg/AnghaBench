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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct nvram_header {scalar_t__ magic; int len; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (struct mtd_info*) ; 
 scalar_t__ NVRAM_MAGIC ; 
 int NVRAM_SPACE ; 
 struct mtd_info* get_mtd_device_nm (char*) ; 
 int mtd_read (struct mtd_info*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ nvram_buf ; 
 int nvram_len ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int nvram_init(void)
{
#ifdef CONFIG_MTD
	struct mtd_info *mtd;
	struct nvram_header header;
	size_t bytes_read;
	int err;

	mtd = get_mtd_device_nm("nvram");
	if (IS_ERR(mtd))
		return -ENODEV;

	err = mtd_read(mtd, 0, sizeof(header), &bytes_read, (uint8_t *)&header);
	if (!err && header.magic == NVRAM_MAGIC &&
	    header.len > sizeof(header)) {
		nvram_len = header.len;
		if (nvram_len >= NVRAM_SPACE) {
			pr_err("nvram on flash (%zu bytes) is bigger than the reserved space in memory, will just copy the first %i bytes\n",
				nvram_len, NVRAM_SPACE);
			nvram_len = NVRAM_SPACE - 1;
		}

		err = mtd_read(mtd, 0, nvram_len, &nvram_len,
			       (u8 *)nvram_buf);
		return err;
	}
#endif

	return -ENXIO;
}