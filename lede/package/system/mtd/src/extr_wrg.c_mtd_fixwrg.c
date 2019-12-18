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
struct wrg_header {int /*<<< orphan*/  size; int /*<<< orphan*/  magic1; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int WRG_MAGIC ; 
 int /*<<< orphan*/  close (int) ; 
 int erasesize ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int mtd_check_open (char const*) ; 
 scalar_t__ mtd_erase_block (int,size_t) ; 
 size_t mtdsize ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pread (int,char*,int,size_t) ; 
 int pwrite (int,char*,int,size_t) ; 
 int quiet ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 scalar_t__ wrg_fix_md5 (struct wrg_header*,int,size_t,size_t) ; 

int
mtd_fixwrg(const char *mtd, size_t offset, size_t data_size)
{
	int fd;
	char *first_block;
	ssize_t res;
	size_t block_offset;
	size_t data_offset;
	struct wrg_header *shdr;

	if (quiet < 2)
		fprintf(stderr, "Trying to fix WRG header in %s at 0x%x...\n",
			mtd, offset);

	block_offset = offset & ~(erasesize - 1);
	offset -= block_offset;

	fd = mtd_check_open(mtd);
	if(fd < 0) {
		fprintf(stderr, "Could not open mtd device: %s\n", mtd);
		exit(1);
	}

	if (block_offset + erasesize > mtdsize) {
		fprintf(stderr, "Offset too large, device size 0x%x\n",
			mtdsize);
		exit(1);
	}

	first_block = malloc(erasesize);
	if (!first_block) {
		perror("malloc");
		exit(1);
	}

	res = pread(fd, first_block, erasesize, block_offset);
	if (res != erasesize) {
		perror("pread");
		exit(1);
	}

	shdr = (struct wrg_header *)(first_block + offset);
	if (le32_to_cpu(shdr->magic1) != WRG_MAGIC) {
		fprintf(stderr, "No WRG header found (%08x != %08x)\n",
		        le32_to_cpu(shdr->magic1), WRG_MAGIC);
		exit(1);
	} else if (!le32_to_cpu(shdr->size)) {
		fprintf(stderr, "WRG entity with empty image\n");
		exit(1);
	}

	data_offset = offset + sizeof(struct wrg_header);
	if (!data_size)
		data_size = mtdsize - data_offset;
	if (data_size > le32_to_cpu(shdr->size))
		data_size = le32_to_cpu(shdr->size);
	if (wrg_fix_md5(shdr, fd, data_offset, data_size))
		goto out;

	if (mtd_erase_block(fd, block_offset)) {
		fprintf(stderr, "Can't erease block at 0x%x (%s)\n",
			block_offset, strerror(errno));
		exit(1);
	}

	if (quiet < 2)
		fprintf(stderr, "Rewriting block at 0x%x\n", block_offset);

	if (pwrite(fd, first_block, erasesize, block_offset) != erasesize) {
		fprintf(stderr, "Error writing block (%s)\n", strerror(errno));
		exit(1);
	}

	if (quiet < 2)
		fprintf(stderr, "Done.\n");

out:
	close (fd);
	sync();

	return 0;
}