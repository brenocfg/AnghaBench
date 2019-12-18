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
struct stat {int st_size; } ;
typedef  int ssize_t ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int EINVAL ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ftruncate (int,int) ; 
 int kqueue () ; 
 int* lengths ; 
 int lengths_count ; 
 int open (char*,int,...) ; 
 scalar_t__ pipe (int*) ; 
 int pread (int,char*,int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
main(void)
{
	int error, fd, fds[2], i, read_only_fd;
	char path[] = "ftruncate_file";
	struct stat sb;
	ssize_t size;
	off_t len;
	char ch;

	/*
	 * Tests using a writable file: grow and then shrink a file
	 * using ftruncate and various lengths.  Make sure that a negative
	 * file length is rejected.  Make sure that when we grow the file,
	 * bytes now in the range of the file size return 0.
	 *
	 * Save a read-only reference to the file to use later for read-only
	 * descriptor tests.
	 */
	fd = open(path, O_RDWR|O_CREAT, 0600);
	if (fd < 0)
		err(1, "open(%s, O_RDWR|O_CREAT, 0600)", path);
	read_only_fd = open(path, O_RDONLY);
	if (read_only_fd < 0) {
		error = errno;
		(void)unlink(path);
		errno = error;
		err(1, "open(%s, O_RDONLY)", path);
	}
	(void)unlink(path);

	if (ftruncate(fd, -1) == 0)
		errx(1, "ftruncate(fd, -1) succeeded unexpectedly");
	if (errno != EINVAL)
		err(1, "ftruncate(fd, -1) returned wrong error");

	for (i = 0; i < lengths_count; i++) {
		len = lengths[i];
		if (ftruncate(fd, len) < 0)
			err(1, "ftruncate(%jd) up", (intmax_t)len);
		if (fstat(fd, &sb) < 0)
			err(1, "stat");
		if (sb.st_size != len)
			errx(-1, "fstat with len=%jd returned len %jd up",
			    (intmax_t)len, (intmax_t)sb.st_size);
		if (len != 0) {
			size = pread(fd, &ch, sizeof(ch), len - 1);
			if (size < 0)
				err(1, "pread on len %jd up", (intmax_t)len);
			if (size != sizeof(ch))
				errx(-1, "pread len %jd size %jd up",
				    (intmax_t)len, (intmax_t)size);
			if (ch != 0)
				errx(-1,
				    "pread length %jd size %jd ch %d up",
				    (intmax_t)len, (intmax_t)size, ch);
		}
	}

	for (i = lengths_count - 1; i >= 0; i--) {
		len = lengths[i];
		if (ftruncate(fd, len) < 0)
			err(1, "ftruncate(%jd) down", (intmax_t)len);
		if (fstat(fd, &sb) < 0)
			err(1, "stat");
		if (sb.st_size != len)
			errx(-1, "fstat(%jd) returned %jd down", (intmax_t)len,
			    sb.st_size);
	}
	close(fd);

	/*
	 * Make sure that a read-only descriptor can't be truncated.
	 */
	if (ftruncate(read_only_fd, 0) == 0)
		errx(-1, "ftruncate(read_only_fd) succeeded");
	if (errno != EINVAL)
		err(1, "ftruncate(read_only_fd) returned wrong error");
	close(read_only_fd);

	/*
	 * Make sure that ftruncate on sockets doesn't work.
	 */
	fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (fd < 0)
		err(1, "socket(PF_UNIX, SOCK_STREAM, 0)");
	if (ftruncate(fd, 0) == 0)
		errx(-1, "ftruncate(socket) succeeded");
	if (errno != EINVAL)
		err(1, "ftruncate(socket) returned wrong error");
	close(fd);

	/*
	 * Make sure that ftruncate on pipes doesn't work.
	 */
	if (pipe(fds) < 0)
		err(1, "pipe");
	if (ftruncate(fds[0], 0) == 0)
		errx(-1, "ftruncate(pipe) succeeded");
	if (errno != EINVAL)
		err(1, "ftruncate(pipe) returned wrong error");
	close(fds[0]);
	close(fds[1]);

	/*
	 * Make sure that ftruncate on kqueues doesn't work.
	 */
	fd = kqueue();
	if (fd < 0)
		err(1, "kqueue");
	if (ftruncate(fds[0], 0) == 0)
		errx(-1, "ftruncate(kqueue) succeeded");
	if (errno != EINVAL)
		err(1, "ftruncate(kqueue) returned wrong error");
	close(fd);

	return (0);
}