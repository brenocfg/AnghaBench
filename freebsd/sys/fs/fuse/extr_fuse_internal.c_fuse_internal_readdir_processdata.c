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
typedef  scalar_t__ u_long ;
struct uio {int dummy; } ;
struct pseudo_dirent {int dummy; } ;
struct fuse_iov {int /*<<< orphan*/  len; scalar_t__ base; } ;
struct fuse_dirent {char* namelen; scalar_t__ off; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; } ;
struct dirent {int d_reclen; char* d_namlen; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_fileno; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t FUSE_DIRENT_SIZE (struct fuse_dirent*) ; 
 size_t FUSE_NAME_OFFSET ; 
 int GENERIC_DIRSIZ (struct pseudo_dirent*) ; 
 char* MAXNAMLEN ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  dirent_terminate (struct dirent*) ; 
 int /*<<< orphan*/  fiov_adjust (struct fuse_iov*,int) ; 
 scalar_t__ isbzero (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (int,char*,char*) ; 
 int uio_resid (struct uio*) ; 
 int /*<<< orphan*/  uio_setoffset (struct uio*,scalar_t__) ; 
 int uiomove (scalar_t__,int /*<<< orphan*/ ,struct uio*) ; 

int
fuse_internal_readdir_processdata(struct uio *uio,
    off_t startoff,
    int *fnd_start,
    size_t reqsize,
    void *buf,
    size_t bufsize,
    struct fuse_iov *cookediov,
    int *ncookies,
    u_long **cookiesp)
{
	int err = 0;
	int bytesavail;
	size_t freclen;

	struct dirent *de;
	struct fuse_dirent *fudge;
	u_long *cookies;

	cookies = *cookiesp;
	if (bufsize < FUSE_NAME_OFFSET)
		return -1;
	for (;;) {
		if (bufsize < FUSE_NAME_OFFSET) {
			err = -1;
			break;
		}
		fudge = (struct fuse_dirent *)buf;
		freclen = FUSE_DIRENT_SIZE(fudge);

		if (bufsize < freclen) {
			/*
			 * This indicates a partial directory entry at the
			 * end of the directory data.
			 */
			err = -1;
			break;
		}
#ifdef ZERO_PAD_INCOMPLETE_BUFS
		if (isbzero(buf, FUSE_NAME_OFFSET)) {
			err = -1;
			break;
		}
#endif

		if (!fudge->namelen || fudge->namelen > MAXNAMLEN) {
			err = EINVAL;
			break;
		}
		bytesavail = GENERIC_DIRSIZ((struct pseudo_dirent *)
					    &fudge->namelen);

		if (bytesavail > uio_resid(uio)) {
			/* Out of space for the dir so we are done. */
			err = -1;
			break;
		}
		/*
		 * Don't start to copy the directory entries out until
		 * the requested offset in the directory is found.
		 */
		if (*fnd_start != 0) {
			fiov_adjust(cookediov, bytesavail);
			bzero(cookediov->base, bytesavail);

			de = (struct dirent *)cookediov->base;
			de->d_fileno = fudge->ino;
			de->d_reclen = bytesavail;
			de->d_type = fudge->type;
			de->d_namlen = fudge->namelen;
			memcpy((char *)cookediov->base + sizeof(struct dirent) -
			       MAXNAMLEN - 1,
			       (char *)buf + FUSE_NAME_OFFSET, fudge->namelen);
			dirent_terminate(de);

			err = uiomove(cookediov->base, cookediov->len, uio);
			if (err)
				break;
			if (cookies != NULL) {
				if (*ncookies == 0) {
					err = -1;
					break;
				}
				*cookies = fudge->off;
				cookies++;
				(*ncookies)--;
			}
		} else if (startoff == fudge->off)
			*fnd_start = 1;
		buf = (char *)buf + freclen;
		bufsize -= freclen;
		uio_setoffset(uio, fudge->off);
	}
	*cookiesp = cookies;

	return err;
}