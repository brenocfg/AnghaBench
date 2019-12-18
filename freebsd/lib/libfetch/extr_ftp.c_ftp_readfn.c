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
struct ftpio {scalar_t__ dir; scalar_t__ err; int eof; int /*<<< orphan*/ * dconn; int /*<<< orphan*/ * cconn; } ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINTR ; 
 scalar_t__ O_WRONLY ; 
 scalar_t__ errno ; 
 int fetch_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ftp_readfn(void *v, char *buf, int len)
{
	struct ftpio *io;
	int r;

	io = (struct ftpio *)v;
	if (io == NULL) {
		errno = EBADF;
		return (-1);
	}
	if (io->cconn == NULL || io->dconn == NULL || io->dir == O_WRONLY) {
		errno = EBADF;
		return (-1);
	}
	if (io->err) {
		errno = io->err;
		return (-1);
	}
	if (io->eof)
		return (0);
	r = fetch_read(io->dconn, buf, len);
	if (r > 0)
		return (r);
	if (r == 0) {
		io->eof = 1;
		return (0);
	}
	if (errno != EINTR)
		io->err = errno;
	return (-1);
}