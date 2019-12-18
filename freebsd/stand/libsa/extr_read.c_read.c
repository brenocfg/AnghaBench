#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct open_file {int f_flags; size_t f_offset; size_t f_ralen; void* f_rabuf; int f_raoffset; TYPE_2__* f_ops; int /*<<< orphan*/  f_devdata; TYPE_1__* f_dev; } ;
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ (* fo_read ) (struct open_file*,void*,size_t,size_t*) ;} ;
struct TYPE_3__ {scalar_t__ (* dv_strategy ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,void*,size_t*) ;} ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 int F_RAW ; 
 int F_READ ; 
 unsigned int SOPEN_MAX ; 
 size_t SOPEN_RASIZE ; 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 int /*<<< orphan*/  btodb (size_t) ; 
 scalar_t__ errno ; 
 struct open_file* files ; 
 size_t imin (size_t,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,void*,size_t*) ; 
 scalar_t__ stub2 (struct open_file*,void*,size_t,size_t*) ; 
 scalar_t__ stub3 (struct open_file*,void*,size_t,size_t*) ; 
 int /*<<< orphan*/  twiddle (int) ; 

ssize_t
read(int fd, void *dest, size_t bcount)
{
	struct open_file *f = &files[fd];
	size_t resid;

	if ((unsigned)fd >= SOPEN_MAX || !(f->f_flags & F_READ)) {
		errno = EBADF;
		return (-1);
	}
	if (f->f_flags & F_RAW) {
		twiddle(4);
		errno = (f->f_dev->dv_strategy)(f->f_devdata, F_READ,
		    btodb(f->f_offset), bcount, dest, &resid);
		if (errno)
			return (-1);
		f->f_offset += resid;
		return (resid);
	}

	/*
	 * Optimise reads from regular files using a readahead buffer.
	 * If the request can't be satisfied from the current buffer contents,
	 * check to see if it should be bypassed, or refill the buffer and
	 * complete the request.
	 */
	resid = bcount;
	for (;;) {
		size_t	ccount, cresid;
		/* how much can we supply? */
		ccount = imin(f->f_ralen, resid);
		if (ccount > 0) {
			bcopy(f->f_rabuf + f->f_raoffset, dest, ccount);
			f->f_raoffset += ccount;
			f->f_ralen -= ccount;
			resid -= ccount;
			if (resid == 0)
				return (bcount);
			dest = (char *)dest + ccount;
		}

		/* will filling the readahead buffer again not help? */
		if (f->f_rabuf == NULL || resid >= SOPEN_RASIZE) {
			/*
			 * bypass the rest of the request and leave the
			 * buffer empty
			 */
			errno = (f->f_ops->fo_read)(f, dest, resid, &cresid);
			if (errno != 0)
				return (-1);
			return (bcount - cresid);
		}

		/* fetch more data */
		errno = (f->f_ops->fo_read)(f, f->f_rabuf, SOPEN_RASIZE,
		    &cresid);
		if (errno != 0)
			return (-1);
		f->f_raoffset = 0;
		f->f_ralen = SOPEN_RASIZE - cresid;
		/* no more data, return what we had */
		if (f->f_ralen == 0)
			return (bcount - resid);
	}
}