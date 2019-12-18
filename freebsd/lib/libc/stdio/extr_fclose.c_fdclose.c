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
struct TYPE_5__ {scalar_t__ _flags; scalar_t__ _close; int _file; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EBADF ; 
 int EOF ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 scalar_t__ __sclose ; 
 int cleanfile (TYPE_1__*,int) ; 
 int errno ; 

int
fdclose(FILE *fp, int *fdp)
{
	int r, err;

	if (fdp != NULL)
		*fdp = -1;

	if (fp->_flags == 0) {	/* not open! */
		errno = EBADF;
		return (EOF);
	}

	FLOCKFILE_CANCELSAFE(fp);
	r = 0;
	if (fp->_close != __sclose) {
		r = EOF;
		errno = EOPNOTSUPP;
	} else if (fp->_file < 0) {
		r = EOF;
		errno = EBADF;
	}
	if (r == EOF) {
		err = errno;
		(void)cleanfile(fp, true);
		errno = err;
	} else {
		if (fdp != NULL)
			*fdp = fp->_file;
		r = cleanfile(fp, false);
	}
	FUNLOCKFILE_CANCELSAFE();

	return (r);
}