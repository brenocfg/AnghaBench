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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 char* MAP_FAILED ; 
 int MAP_FILE ; 
 int MAP_PRIVATE ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 scalar_t__ memcmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msync (char*,size_t,int) ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 
 scalar_t__ off ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 size_t page ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int write (int,char const*,size_t) ; 

__attribute__((used)) static const char *
msync_sync(const char *garbage, int flags)
{
	char *buf, *map = MAP_FAILED;
	const char *str = NULL;
	size_t len;
	int fd, rv;

	/*
	 * Create a temporary file, write
	 * one page to it, and map the file.
	 */
	buf = malloc(page);

	if (buf == NULL)
		return NULL;

	memset(buf, 'x', page);

	fd = open(path, O_RDWR | O_CREAT, 0700);

	if (fd < 0) {
		free(buf);
		return "failed to open";
	}

	ATF_REQUIRE_MSG(write(fd, buf, page) != -1, "write(2) failed: %s",
	    strerror(errno));

	map = mmap(NULL, page, PROT_READ | PROT_WRITE, MAP_FILE|MAP_PRIVATE,
	     fd, 0);

	if (map == MAP_FAILED) {
		str = "failed to map";
		goto out;
	}

	/*
	 * Seek to an arbitrary offset and
	 * write garbage to this position.
	 */
	if (lseek(fd, off, SEEK_SET) != off) {
		str = "failed to seek";
		goto out;
	}

	len = strlen(garbage);
	rv = write(fd, garbage, len);

	if (rv != (ssize_t)len) {
		str = "failed to write garbage";
		goto out;
	}

	/*
	 * Synchronize the mapping and verify
	 * that garbage is at the given offset.
	 */
	if (msync(map, page, flags) != 0) {
		str = "failed to msync";
		goto out;
	}

	if (memcmp(map + off, garbage, len) != 0) {
		str = "msync did not synchronize";
		goto out;
	}

out:
	free(buf);

	(void)close(fd);
	(void)unlink(path);

	if (map != MAP_FAILED)
		(void)munmap(map, page);

	return str;
}