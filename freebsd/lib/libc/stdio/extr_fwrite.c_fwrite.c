#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct __suio {size_t uio_resid; int uio_iovcnt; struct __siov* uio_iov; } ;
struct __siov {size_t iov_len; void* iov_base; } ;
struct TYPE_6__ {int /*<<< orphan*/  _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int /*<<< orphan*/  ORIENT (TYPE_1__*,int) ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  __SERR ; 
 scalar_t__ __sfvwrite (TYPE_1__*,struct __suio*) ; 
 int /*<<< orphan*/  errno ; 

size_t
fwrite(const void * __restrict buf, size_t size, size_t count, FILE * __restrict fp)
{
	size_t n;
	struct __suio uio;
	struct __siov iov;

	/*
	 * ANSI and SUSv2 require a return value of 0 if size or count are 0.
	 */
	if ((count == 0) || (size == 0))
		return (0);

	/*
	 * Check for integer overflow.  As an optimization, first check that
	 * at least one of {count, size} is at least 2^16, since if both
	 * values are less than that, their product can't possibly overflow
	 * (size_t is always at least 32 bits on FreeBSD).
	 */
	if (((count | size) > 0xFFFF) &&
	    (count > SIZE_MAX / size)) {
		errno = EINVAL;
		fp->_flags |= __SERR;
		return (0);
	}

	n = count * size;

	iov.iov_base = (void *)buf;
	uio.uio_resid = iov.iov_len = n;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;

	FLOCKFILE_CANCELSAFE(fp);
	ORIENT(fp, -1);
	/*
	 * The usual case is success (__sfvwrite returns 0);
	 * skip the divide if this happens, since divides are
	 * generally slow and since this occurs whenever size==0.
	 */
	if (__sfvwrite(fp, &uio) != 0)
	    count = (n - uio.uio_resid) / size;
	FUNLOCKFILE_CANCELSAFE();
	return (count);
}