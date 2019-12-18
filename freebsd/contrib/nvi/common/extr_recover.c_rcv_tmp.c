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
struct stat {int dummy; } ;
struct TYPE_4__ {char* rcv_path; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EXF ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_RCV_ON ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_RECDIR ; 
 char* O_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join (char*,char*) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ opts_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rcv_mktemp (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int
rcv_tmp(
	SCR *sp,
	EXF *ep,
	char *name)
{
	struct stat sb;
	int fd;
	char *dp, *path;

	/*
	 * !!!
	 * ep MAY NOT BE THE SAME AS sp->ep, DON'T USE THE LATTER.
	 *
	 *
	 * If the recovery directory doesn't exist, try and create it.  As
	 * the recovery files are themselves protected from reading/writing
	 * by other than the owner, the worst that can happen is that a user
	 * would have permission to remove other user's recovery files.  If
	 * the sticky bit has the BSD semantics, that too will be impossible.
	 */
	if (opts_empty(sp, O_RECDIR, 0))
		goto err;
	dp = O_STR(sp, O_RECDIR);
	if (stat(dp, &sb)) {
		if (errno != ENOENT || mkdir(dp, 0)) {
			msgq(sp, M_SYSERR, "%s", dp);
			goto err;
		}
		(void)chmod(dp, S_IRWXU | S_IRWXG | S_IRWXO | S_ISVTX);
	}

	if ((path = join(dp, "vi.XXXXXX")) == NULL)
		goto err;
	if ((fd = rcv_mktemp(sp, path, dp)) == -1) {
		free(path);
		goto err;
	}
	(void)fchmod(fd, S_IRWXU);
	(void)close(fd);

	ep->rcv_path = path;
	if (0) {
err:		msgq(sp, M_ERR,
		    "056|Modifications not recoverable if the session fails");
		return (1);
	}

	/* We believe the file is recoverable. */
	F_SET(ep, F_RCV_ON);
	return (0);
}