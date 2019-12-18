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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int O_APPEND ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_VERIFY ; 
 int O_WRONLY ; 
 int __SRD ; 
 int __SRW ; 
 int __SWR ; 
 int /*<<< orphan*/  errno ; 

int
__sflags(const char *mode, int *optr)
{
	int ret, m, o, known;

	switch (*mode++) {

	case 'r':	/* open for reading */
		ret = __SRD;
		m = O_RDONLY;
		o = 0;
		break;

	case 'w':	/* open for writing */
		ret = __SWR;
		m = O_WRONLY;
		o = O_CREAT | O_TRUNC;
		break;

	case 'a':	/* open for appending */
		ret = __SWR;
		m = O_WRONLY;
		o = O_CREAT | O_APPEND;
		break;

	default:	/* illegal mode */
		errno = EINVAL;
		return (0);
	}

	do {
		known = 1;
		switch (*mode++) {
		case 'b':
			/* 'b' (binary) is ignored */
			break;
		case '+':
			/* [rwa][b]\+ means read and write */
			ret = __SRW;
			m = O_RDWR;
			break;
		case 'x':
			/* 'x' means exclusive (fail if the file exists) */
			o |= O_EXCL;
			break;
		case 'e':
			/* set close-on-exec */
			o |= O_CLOEXEC;
			break;
		case 'v':
			/* verify */
			o |= O_VERIFY;
			break;
		default:
			known = 0;
			break;
		}
	} while (known);

	if ((o & O_EXCL) != 0 && m == O_RDONLY) {
		errno = EINVAL;
		return (0);
	}

	*optr = m | o;
	return (ret);
}