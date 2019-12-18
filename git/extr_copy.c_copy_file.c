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

/* Variables and functions */
#define  COPY_READ_ERROR 129 
#define  COPY_WRITE_ERROR 128 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 scalar_t__ adjust_shared_perm (char const*) ; 
 scalar_t__ close (int) ; 
 int copy_fd (int,int) ; 
 int error_errno (char*,...) ; 
 int open (char const*,int,...) ; 

int copy_file(const char *dst, const char *src, int mode)
{
	int fdi, fdo, status;

	mode = (mode & 0111) ? 0777 : 0666;
	if ((fdi = open(src, O_RDONLY)) < 0)
		return fdi;
	if ((fdo = open(dst, O_WRONLY | O_CREAT | O_EXCL, mode)) < 0) {
		close(fdi);
		return fdo;
	}
	status = copy_fd(fdi, fdo);
	switch (status) {
	case COPY_READ_ERROR:
		error_errno("copy-fd: read returned");
		break;
	case COPY_WRITE_ERROR:
		error_errno("copy-fd: write returned");
		break;
	}
	close(fdi);
	if (close(fdo) != 0)
		return error_errno("%s: close error", dst);

	if (!status && adjust_shared_perm(dst))
		return -1;

	return status;
}