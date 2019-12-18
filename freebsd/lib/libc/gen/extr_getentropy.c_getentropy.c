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
typedef  int ssize_t ;

/* Variables and functions */
#define  ECAPMODE 130 
#define  EFAULT 129 
#define  EINTR 128 
 int EIO ; 
 scalar_t__ GETRANDOM_FIRST ; 
 scalar_t__ __getosreldate () ; 
 int /*<<< orphan*/  _getentropy_fail () ; 
 int errno ; 
 int getentropy_fallback (void*,size_t) ; 
 int getrandom (void*,size_t,int /*<<< orphan*/ ) ; 

int
getentropy(void *buf, size_t buflen)
{
	ssize_t rd;
	bool have_getrandom;

	if (buflen > 256) {
		errno = EIO;
		return (-1);
	}

	have_getrandom = (__getosreldate() >= GETRANDOM_FIRST);

	while (buflen > 0) {
		if (have_getrandom) {
			rd = getrandom(buf, buflen, 0);
			if (rd == -1) {
				switch (errno) {
				case ECAPMODE:
					/*
					 * Kernel >= r331280 and < r337999
					 * will return ECAPMODE when the
					 * caller is already in capability
					 * mode, fallback to traditional
					 * method in this case.
					 */
					have_getrandom = false;
					continue;
				case EINTR:
					continue;
				case EFAULT:
					return (-1);
				default:
					_getentropy_fail();
				}
			}
		} else {
			return (getentropy_fallback(buf, buflen));
		}

		/* This cannot happen. */
		if (rd == 0)
			_getentropy_fail();

		buf = (char *)buf + rd;
		buflen -= rd;
	}

	return (0);
}