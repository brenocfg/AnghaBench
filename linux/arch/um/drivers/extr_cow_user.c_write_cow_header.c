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
struct cow_header_v3 {char* backing_file; int /*<<< orphan*/  cow_format; void* alignment; void* sectorsize; int /*<<< orphan*/  size; void* mtime; void* version; void* magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  COW_BITMAP ; 
 int COW_MAGIC ; 
 int COW_VERSION ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ absolutize (char*,int,char*) ; 
 int cow_file_size (char*,unsigned long long*) ; 
 int /*<<< orphan*/  cow_free (struct cow_header_v3*) ; 
 struct cow_header_v3* cow_malloc (int) ; 
 int /*<<< orphan*/  cow_printf (char*,...) ; 
 int cow_seek_file (int,int /*<<< orphan*/ ) ; 
 int cow_write_file (int,struct cow_header_v3*,int) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  htobe64 (unsigned long long) ; 
 int os_file_modtime (char*,unsigned long*) ; 
 int strlen (char*) ; 

int write_cow_header(char *cow_file, int fd, char *backing_file,
		     int sectorsize, int alignment, unsigned long long *size)
{
	struct cow_header_v3 *header;
	unsigned long modtime;
	int err;

	err = cow_seek_file(fd, 0);
	if (err < 0) {
		cow_printf("write_cow_header - lseek failed, err = %d\n", -err);
		goto out;
	}

	err = -ENOMEM;
	header = cow_malloc(sizeof(*header));
	if (header == NULL) {
		cow_printf("write_cow_header - failed to allocate COW V3 "
			   "header\n");
		goto out;
	}
	header->magic = htobe32(COW_MAGIC);
	header->version = htobe32(COW_VERSION);

	err = -EINVAL;
	if (strlen(backing_file) > sizeof(header->backing_file) - 1) {
		/* Below, %zd is for a size_t value */
		cow_printf("Backing file name \"%s\" is too long - names are "
			   "limited to %zd characters\n", backing_file,
			   sizeof(header->backing_file) - 1);
		goto out_free;
	}

	if (absolutize(header->backing_file, sizeof(header->backing_file),
		      backing_file))
		goto out_free;

	err = os_file_modtime(header->backing_file, &modtime);
	if (err < 0) {
		cow_printf("write_cow_header - backing file '%s' mtime "
			   "request failed, err = %d\n", header->backing_file,
			   -err);
		goto out_free;
	}

	err = cow_file_size(header->backing_file, size);
	if (err < 0) {
		cow_printf("write_cow_header - couldn't get size of "
			   "backing file '%s', err = %d\n",
			   header->backing_file, -err);
		goto out_free;
	}

	header->mtime = htobe32(modtime);
	header->size = htobe64(*size);
	header->sectorsize = htobe32(sectorsize);
	header->alignment = htobe32(alignment);
	header->cow_format = COW_BITMAP;

	err = cow_write_file(fd, header, sizeof(*header));
	if (err != sizeof(*header)) {
		cow_printf("write_cow_header - write of header to "
			   "new COW file '%s' failed, err = %d\n", cow_file,
			   -err);
		goto out_free;
	}
	err = 0;
 out_free:
	cow_free(header);
 out:
	return err;
}