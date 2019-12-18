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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int /*<<< orphan*/ ,size_t,char*,char const*,...) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  atf_utils_cat_file (char const*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ file_size_from_fd (int) ; 
 int /*<<< orphan*/  lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char*,char*,size_t) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_source_and_dest(const char* dest_filename, int src_fd, off_t offset,
    size_t nbytes)
{
	char *dest_pointer, *src_pointer;
	off_t dest_file_size, src_file_size;
	size_t length;
	int dest_fd;

	atf_utils_cat_file(dest_filename, "dest_file: ");

	dest_fd = open(dest_filename, O_RDONLY);
	ATF_REQUIRE_MSG(dest_fd != -1, "open failed");

	dest_file_size = file_size_from_fd(dest_fd);
	src_file_size = file_size_from_fd(src_fd);

	/*
	 * Per sendfile(2), "send the whole file" (paraphrased). This means
	 * that we need to grab the file size, as passing in length = 0 with
	 * mmap(2) will result in a failure with EINVAL (length = 0 is invalid).
	 */
	length = (nbytes == 0) ? (size_t)(src_file_size - offset) : nbytes;

	ATF_REQUIRE_EQ_MSG(dest_file_size, length,
	    "number of bytes written out to %s (%ju) doesn't match the "
	    "expected number of bytes (%zu)", dest_filename, dest_file_size,
	    length);

	ATF_REQUIRE_EQ_MSG(0, lseek(src_fd, offset, SEEK_SET),
	    "lseek failed: %s", strerror(errno));

	dest_pointer = mmap(NULL, length, PROT_READ, MAP_PRIVATE, dest_fd, 0);
	ATF_REQUIRE_MSG(dest_pointer != MAP_FAILED, "mmap failed: %s",
	    strerror(errno));

	printf("Will mmap in the source file from offset=%jd to length=%zu\n",
	    offset, length);

	src_pointer = mmap(NULL, length, PROT_READ, MAP_PRIVATE, src_fd, offset);
	ATF_REQUIRE_MSG(src_pointer != MAP_FAILED, "mmap failed: %s",
	    strerror(errno));

	ATF_REQUIRE_EQ_MSG(0, memcmp(src_pointer, dest_pointer, length),
	    "Contents of source and destination do not match. '%s' != '%s'",
	    src_pointer, dest_pointer);

	(void)munmap(src_pointer, length);
	(void)munmap(dest_pointer, length);
	(void)close(dest_fd);
}