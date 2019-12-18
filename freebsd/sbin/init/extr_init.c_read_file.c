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
struct stat {size_t st_size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int close (int) ; 
 int /*<<< orphan*/  emergency (char*,char const*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int fstat (int,struct stat*) ; 
 void* malloc (size_t) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,void*,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_file(const char *path, void **bufp, size_t *bufsizep)
{
	struct stat sb;
	size_t bufsize;
	void *buf;
	ssize_t nbytes;
	int error, fd;

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		emergency("%s: %s", path, strerror(errno));
		return (-1);
	}

	error = fstat(fd, &sb);
	if (error != 0) {
		emergency("fstat: %s", strerror(errno));
		close(fd);
		return (error);
	}

	bufsize = sb.st_size;
	buf = malloc(bufsize);
	if (buf == NULL) {
		emergency("malloc: %s", strerror(errno));
		close(fd);
		return (error);
	}

	nbytes = read(fd, buf, bufsize);
	if (nbytes != (ssize_t)bufsize) {
		emergency("read: %s", strerror(errno));
		close(fd);
		free(buf);
		return (error);
	}

	error = close(fd);
	if (error != 0) {
		emergency("close: %s", strerror(errno));
		free(buf);
		return (error);
	}

	*bufp = buf;
	*bufsizep = bufsize;

	return (0);
}