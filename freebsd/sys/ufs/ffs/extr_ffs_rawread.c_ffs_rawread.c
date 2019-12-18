#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; scalar_t__ uio_segflg; scalar_t__ uio_resid; int uio_offset; TYPE_3__* uio_td; TYPE_1__* uio_iov; } ;
struct inode {int i_size; } ;
typedef  int off_t ;
struct TYPE_7__ {int bo_bsize; } ;
struct TYPE_10__ {TYPE_2__ v_bufobj; } ;
struct TYPE_9__ {unsigned int fs_bsize; } ;
struct TYPE_8__ {int td_pflags; } ;
struct TYPE_6__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 TYPE_5__* ITODEVVP (struct inode*) ; 
 TYPE_4__* ITOFS (struct inode*) ; 
 int TDP_DEADLKTREAT ; 
 scalar_t__ UIO_USERSPACE ; 
 struct inode* VTOI (struct vnode*) ; 
 scalar_t__ allowrawread ; 
 TYPE_3__* curthread ; 
 int ffs_rawread_main (struct vnode*,struct uio*) ; 
 int ffs_rawread_sync (struct vnode*) ; 

int
ffs_rawread(struct vnode *vp,
	    struct uio *uio,
	    int *workdone)
{
	if (allowrawread != 0 &&
	    uio->uio_iovcnt == 1 && 
	    uio->uio_segflg == UIO_USERSPACE &&
	    uio->uio_resid == uio->uio_iov->iov_len &&
	    (((uio->uio_td != NULL) ? uio->uio_td : curthread)->td_pflags &
	     TDP_DEADLKTREAT) == 0) {
		int secsize;		/* Media sector size */
		off_t filebytes;	/* Bytes left of file */
		int blockbytes;		/* Bytes left of file in full blocks */
		int partialbytes;	/* Bytes in last partial block */
		int skipbytes;		/* Bytes not to read in ffs_rawread */
		struct inode *ip;
		int error;
		

		/* Only handle sector aligned reads */
		ip = VTOI(vp);
		secsize = ITODEVVP(ip)->v_bufobj.bo_bsize;
		if ((uio->uio_offset & (secsize - 1)) == 0 &&
		    (uio->uio_resid & (secsize - 1)) == 0) {
			
			/* Sync dirty pages and buffers if needed */
			error = ffs_rawread_sync(vp);
			if (error != 0)
				return error;
			
			/* Check for end of file */
			if (ip->i_size > uio->uio_offset) {
				filebytes = ip->i_size - uio->uio_offset;

				/* No special eof handling needed ? */
				if (uio->uio_resid <= filebytes) {
					*workdone = 1;
					return ffs_rawread_main(vp, uio);
				}
				
				partialbytes = ((unsigned int) ip->i_size) %
				    ITOFS(ip)->fs_bsize;
				blockbytes = (int) filebytes - partialbytes;
				if (blockbytes > 0) {
					skipbytes = uio->uio_resid -
						blockbytes;
					uio->uio_resid = blockbytes;
					error = ffs_rawread_main(vp, uio);
					uio->uio_resid += skipbytes;
					if (error != 0)
						return error;
					/* Read remaining part using buffer */
				}
			}
		}
	}
	*workdone = 0;
	return 0;
}