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
struct mtd_info_user {int size; int writesize; int length; scalar_t__ start; } ;
struct erase_info_user {int size; int writesize; int length; scalar_t__ start; } ;
struct bootcounter {void* magic; int count; void* checksum; } ;

/* Variables and functions */
 void* BOOTCOUNT_MAGIC ; 
 int /*<<< orphan*/  MEMERASE ; 
 int /*<<< orphan*/  MEMGETINFO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mtd_info_user*) ; 
 int /*<<< orphan*/  memset (struct bootcounter*,int,unsigned int) ; 
 int mtd_check_open (char const*) ; 
 scalar_t__ page ; 
 int /*<<< orphan*/  pread (int,struct bootcounter*,int,unsigned int) ; 
 int pwrite (int,struct bootcounter*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sync () ; 

int mtd_resetbc(const char *mtd)
{
	struct mtd_info_user mtd_info;
	struct bootcounter *curr = (struct bootcounter *)page;
	unsigned int i;
	int last_count = 0;
	int num_bc;
	int fd;
	int ret;

	fd = mtd_check_open(mtd);

	if (ioctl(fd, MEMGETINFO, &mtd_info) < 0) {
		fprintf(stderr, "failed to get mtd info!\n");
		return -1;
	}

	num_bc = mtd_info.size / mtd_info.writesize;

	for (i = 0; i < num_bc; i++) {
		pread(fd, curr, sizeof(*curr), i * mtd_info.writesize);

		if (curr->magic != BOOTCOUNT_MAGIC && curr->magic != 0xffffffff) {
			fprintf(stderr, "unexpected magic %08x, bailing out\n", curr->magic);
			goto out;
		}

		if (curr->magic == 0xffffffff)
			break;

		last_count = curr->count;
	}

	/* no need to do writes when last boot count is already 0 */
	if (last_count == 0)
		goto out;


	if (i == num_bc) {
		struct erase_info_user erase_info;
		erase_info.start = 0;
		erase_info.length = mtd_info.size;

		/* erase block */
		ret = ioctl(fd, MEMERASE, &erase_info);
		if (ret < 0) {
			fprintf(stderr, "failed to erase block: %i\n", ret);
			return -1;
		}

		i = 0;
	}

	memset(curr, 0xff, mtd_info.writesize);

	curr->magic = BOOTCOUNT_MAGIC;
	curr->count = 0;
	curr->checksum = BOOTCOUNT_MAGIC;

	ret = pwrite(fd, curr, mtd_info.writesize, i * mtd_info.writesize);
	if (ret < 0)
		fprintf(stderr, "failed to write: %i\n", ret);
	sync();
out:
	close(fd);

	return 0;
}