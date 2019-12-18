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
struct stat {int /*<<< orphan*/  st_mode; scalar_t__ st_size; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ BBSIZE ; 
 int /*<<< orphan*/  DIOCGDELETE ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  O_WRONLY ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int swapon (char const*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
swapon_trim(const char *name)
{
	struct stat sb;
	off_t ioarg[2], sz;
	int error, fd;

	/* Open a descriptor to create a consumer of the device. */
	fd = open(name, O_WRONLY);
	if (fd < 0)
		errx(1, "Cannot open %s", name);
	/* Find the device size. */
	if (fstat(fd, &sb) < 0)
		errx(1, "Cannot stat %s", name);
	if (S_ISREG(sb.st_mode))
		sz = sb.st_size;
	else if (S_ISCHR(sb.st_mode)) {
		if (ioctl(fd, DIOCGMEDIASIZE, &sz) != 0)
			err(1, "ioctl(DIOCGMEDIASIZE)");
	} else
		errx(1, "%s has an invalid file type", name);
	/* Trim the device. */
	ioarg[0] = BBSIZE;
	ioarg[1] = sz - BBSIZE;
	if (ioctl(fd, DIOCGDELETE, ioarg) != 0)
		warn("ioctl(DIOCGDELETE)");

	/* Start using the device for swapping, creating a second consumer. */
	error = swapon(name);

	/*
	 * Do not close the device until the swap pager has attempted to create
	 * another consumer.  For GELI devices created with the 'detach -l'
	 * option, removing the last consumer causes the device to be detached
	 * - that is, to disappear.  This ordering ensures that the device will
	 * not be detached until swapoff is called.
	 */
	close(fd);
	return (error);
}