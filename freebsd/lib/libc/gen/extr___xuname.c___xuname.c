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
 int CTL_HW ; 
 int CTL_KERN ; 
 int ENOMEM ; 
 int HW_MACHINE ; 
 int KERN_HOSTNAME ; 
 int KERN_OSRELEASE ; 
 int KERN_OSTYPE ; 
 int KERN_VERSION ; 
 int errno ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
__xuname(int namesize, void *namebuf)
{
	int mib[2], rval;
	size_t len;
	char *p, *q;
	int oerrno;

	rval = 0;
	q = (char *)namebuf;

	mib[0] = CTL_KERN;

	if ((p = getenv("UNAME_s")))
		strlcpy(q, p, namesize);
	else {
		mib[1] = KERN_OSTYPE;
		len = namesize;
		oerrno = errno;
		if (sysctl(mib, 2, q, &len, NULL, 0) == -1) {
			if (errno == ENOMEM)
				errno = oerrno;
			else
				rval = -1;
		}
		q[namesize - 1] = '\0';
	}
	q += namesize;

	mib[1] = KERN_HOSTNAME;
	len = namesize;
	oerrno = errno;
	if (sysctl(mib, 2, q, &len, NULL, 0) == -1) {
		if (errno == ENOMEM)
			errno = oerrno;
		else
			rval = -1;
	}
	q[namesize - 1] = '\0';
	q += namesize;

	if ((p = getenv("UNAME_r")))
		strlcpy(q, p, namesize);
	else {
		mib[1] = KERN_OSRELEASE;
		len = namesize;
		oerrno = errno;
		if (sysctl(mib, 2, q, &len, NULL, 0) == -1) {
			if (errno == ENOMEM)
				errno = oerrno;
			else
				rval = -1;
		}
		q[namesize - 1] = '\0';
	}
	q += namesize;

	if ((p = getenv("UNAME_v")))
		strlcpy(q, p, namesize);
	else {

		/*
		 * The version may have newlines in it, turn them into
		 * spaces.
		 */
		mib[1] = KERN_VERSION;
		len = namesize;
		oerrno = errno;
		if (sysctl(mib, 2, q, &len, NULL, 0) == -1) {
			if (errno == ENOMEM)
				errno = oerrno;
			else
				rval = -1;
		}
		q[namesize - 1] = '\0';
		for (p = q; len--; ++p) {
			if (*p == '\n' || *p == '\t') {
				if (len > 1)
					*p = ' ';
				else
					*p = '\0';
			}
		}
	}
	q += namesize;

	if ((p = getenv("UNAME_m")))
		strlcpy(q, p, namesize);
	else {
		mib[0] = CTL_HW;
		mib[1] = HW_MACHINE;
		len = namesize;
		oerrno = errno;
		if (sysctl(mib, 2, q, &len, NULL, 0) == -1) {
			if (errno == ENOMEM)
				errno = oerrno;
			else
				rval = -1;
		}
		q[namesize - 1] = '\0';
	}

	return (rval);
}