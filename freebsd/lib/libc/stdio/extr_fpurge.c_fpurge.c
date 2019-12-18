#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  _size; int /*<<< orphan*/  _base; } ;
struct TYPE_9__ {int _flags; TYPE_1__ _bf; int /*<<< orphan*/  _w; scalar_t__ _r; int /*<<< orphan*/  _p; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int EOF ; 
 int /*<<< orphan*/  FLOCKFILE (TYPE_2__*) ; 
 int /*<<< orphan*/  FREEUB (TYPE_2__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE (TYPE_2__*) ; 
 scalar_t__ HASUB (TYPE_2__*) ; 
 int __SLBF ; 
 int __SNBF ; 
 int __SRD ; 
 int /*<<< orphan*/  errno ; 

int
fpurge(FILE *fp)
{
	int retval;
	FLOCKFILE(fp);
	if (!fp->_flags) {
		errno = EBADF;
		retval = EOF;
	} else {
		if (HASUB(fp))
			FREEUB(fp);
		fp->_p = fp->_bf._base;
		fp->_r = 0;
		fp->_w = fp->_flags & (__SLBF|__SNBF|__SRD) ? 0 : fp->_bf._size;
		retval = 0;
	}
	FUNLOCKFILE(fp);
	return (retval);
}