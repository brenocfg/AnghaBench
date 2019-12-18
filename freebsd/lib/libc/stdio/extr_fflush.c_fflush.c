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
struct TYPE_5__ {int _flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int __SRW ; 
 int __SWR ; 
 int __sflush (TYPE_1__*) ; 
 int _fwalk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sflush_locked ; 

int
fflush(FILE *fp)
{
	int retval;

	if (fp == NULL)
		return (_fwalk(sflush_locked));
	FLOCKFILE_CANCELSAFE(fp);

	/*
	 * There is disagreement about the correct behaviour of fflush()
	 * when passed a file which is not open for writing.  According to
	 * the ISO C standard, the behaviour is undefined.
	 * Under linux, such an fflush returns success and has no effect;
	 * under Windows, such an fflush is documented as behaving instead
	 * as fpurge().
	 * Given that applications may be written with the expectation of
	 * either of these two behaviours, the only safe (non-astonishing)
	 * option is to return EBADF and ask that applications be fixed.
	 * SUSv3 now requires that fflush() returns success on a read-only
	 * stream.
	 *
	 */
	if ((fp->_flags & (__SWR | __SRW)) == 0)
		retval = 0;
	else
		retval = __sflush(fp);
	FUNLOCKFILE_CANCELSAFE();
	return (retval);
}