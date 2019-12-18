#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int _r; scalar_t__ _p; int /*<<< orphan*/  _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ORIENT (TYPE_1__*,int) ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  __SERR ; 
 scalar_t__ __srefill (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

size_t
__fread(void * __restrict buf, size_t size, size_t count, FILE * __restrict fp)
{
	size_t resid;
	char *p;
	int r;
	size_t total;

	/*
	 * ANSI and SUSv2 require a return value of 0 if size or count are 0.
	 */
	if ((count == 0) || (size == 0))
		return (0);

	/*
	 * Check for integer overflow.  As an optimization, first check that
	 * at least one of {count, size} is at least 2^16, since if both
	 * values are less than that, their product can't possible overflow
	 * (size_t is always at least 32 bits on FreeBSD).
	 */
	if (((count | size) > 0xFFFF) &&
	    (count > SIZE_MAX / size)) {
		errno = EINVAL;
		fp->_flags |= __SERR;
		return (0);
	}

	/*
	 * Compute the (now required to not overflow) number of bytes to
	 * read and actually do the work.
	 */
	resid = count * size;
	ORIENT(fp, -1);
	if (fp->_r < 0)
		fp->_r = 0;
	total = resid;
	p = buf;
	while (resid > (r = fp->_r)) {
		(void)memcpy((void *)p, (void *)fp->_p, (size_t)r);
		fp->_p += r;
		/* fp->_r = 0 ... done in __srefill */
		p += r;
		resid -= r;
		if (__srefill(fp)) {
			/* no more input: return partial result */
			return ((total - resid) / size);
		}
	}
	(void)memcpy((void *)p, (void *)fp->_p, resid);
	fp->_r -= resid;
	fp->_p += resid;
	return (count);
}