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
typedef  int /*<<< orphan*/  u_long ;
struct open_file {scalar_t__ f_fsdata; } ;
struct nfs_iodesc {scalar_t__ off; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ debug ; 
 int errno ; 
 int nfs_readdata (struct nfs_iodesc*,scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  twiddle (int) ; 

int
nfs_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	struct nfs_iodesc *fp = (struct nfs_iodesc *)f->f_fsdata;
	ssize_t cc;
	char *addr = buf;

#ifdef NFS_DEBUG
	if (debug)
		printf("nfs_read: size=%lu off=%d\n", (u_long)size,
		       (int)fp->off);
#endif
	while ((int)size > 0) {
		twiddle(16);
		cc = nfs_readdata(fp, fp->off, (void *)addr, size);
		/* XXX maybe should retry on certain errors */
		if (cc == -1) {
#ifdef NFS_DEBUG
			if (debug)
				printf("nfs_read: read: %s\n", strerror(errno));
#endif
			return (errno);	/* XXX - from nfs_readdata */
		}
		if (cc == 0) {
#ifdef NFS_DEBUG
			if (debug)
				printf("nfs_read: hit EOF unexpectedly\n");
#endif
			goto ret;
		}
		fp->off += cc;
		addr += cc;
		size -= cc;
	}
ret:
	if (resid)
		*resid = size;

	return (0);
}