#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ftpio {int dir; TYPE_1__* cconn; TYPE_1__* dconn; } ;
struct TYPE_4__ {int ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*) ; 
 int /*<<< orphan*/  EBADF ; 
 int FTP_TRANSFER_COMPLETE ; 
 TYPE_1__* cached_connection ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fetch_close (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct ftpio*) ; 
 int ftp_chkerr (TYPE_1__*) ; 

__attribute__((used)) static int
ftp_closefn(void *v)
{
	struct ftpio *io;
	int r;

	io = (struct ftpio *)v;
	if (io == NULL) {
		errno = EBADF;
		return (-1);
	}
	if (io->dir == -1)
		return (0);
	if (io->cconn == NULL || io->dconn == NULL) {
		errno = EBADF;
		return (-1);
	}
	fetch_close(io->dconn);
	io->dir = -1;
	io->dconn = NULL;
	DEBUGF("Waiting for final status\n");
	r = ftp_chkerr(io->cconn);
	if (io->cconn == cached_connection && io->cconn->ref == 1)
		cached_connection = NULL;
	fetch_close(io->cconn);
	free(io);
	return (r == FTP_TRANSFER_COMPLETE) ? 0 : -1;
}