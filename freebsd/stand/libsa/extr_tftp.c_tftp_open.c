#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tftp_handle {struct tftp_handle* pkt; struct tftp_handle* path; scalar_t__ off; struct iodesc* iodesc; int /*<<< orphan*/  tftp_blksize; } ;
struct open_file {struct tftp_handle* f_fsdata; scalar_t__ f_devdata; TYPE_1__* f_dev; } ;
struct iodesc {int /*<<< orphan*/  destip; } ;
struct TYPE_2__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_NET ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ NET_TFTP ; 
 int /*<<< orphan*/  TFTP_REQUESTED_BLKSIZE ; 
 struct tftp_handle* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct tftp_handle*) ; 
 int is_open ; 
 struct tftp_handle* malloc (size_t) ; 
 scalar_t__ netproto ; 
 char* rootpath ; 
 int /*<<< orphan*/  servip ; 
 int snprintf (struct tftp_handle*,size_t,char*,char*,char const*,char const*) ; 
 struct iodesc* socktodesc (int) ; 
 int strlen (char const*) ; 
 int tftp_makereq (struct tftp_handle*) ; 

__attribute__((used)) static int
tftp_open(const char *path, struct open_file *f)
{
	struct tftp_handle *tftpfile;
	struct iodesc	*io;
	int		res;
	size_t		pathsize;
	const char	*extraslash;

	if (netproto != NET_TFTP)
		return (EINVAL);

	if (f->f_dev->dv_type != DEVT_NET)
		return (EINVAL);

	if (is_open)
		return (EBUSY);

	tftpfile = calloc(1, sizeof(*tftpfile));
	if (!tftpfile)
		return (ENOMEM);

	tftpfile->tftp_blksize = TFTP_REQUESTED_BLKSIZE;
	tftpfile->iodesc = io = socktodesc(*(int *)(f->f_devdata));
	if (io == NULL) {
		free(tftpfile);
		return (EINVAL);
	}

	io->destip = servip;
	tftpfile->off = 0;
	pathsize = (strlen(rootpath) + 1 + strlen(path) + 1) * sizeof(char);
	tftpfile->path = malloc(pathsize);
	if (tftpfile->path == NULL) {
		free(tftpfile);
		return (ENOMEM);
	}
	if (rootpath[strlen(rootpath) - 1] == '/' || path[0] == '/')
		extraslash = "";
	else
		extraslash = "/";
	res = snprintf(tftpfile->path, pathsize, "%s%s%s",
	    rootpath, extraslash, path);
	if (res < 0 || res > pathsize) {
		free(tftpfile->path);
		free(tftpfile);
		return (ENOMEM);
	}

	res = tftp_makereq(tftpfile);

	if (res) {
		free(tftpfile->path);
		free(tftpfile->pkt);
		free(tftpfile);
		return (res);
	}
	f->f_fsdata = tftpfile;
	is_open = 1;
	return (0);
}