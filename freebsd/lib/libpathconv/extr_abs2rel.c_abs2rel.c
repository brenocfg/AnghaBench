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
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

char *
abs2rel(const char *path, const char *base, char *result, const size_t size)
{
	const char *pp, *bp, *branch;
	/*
	 * endp points the last position which is safe in the result buffer.
	 */
	const char *endp = result + size - 1;
	char *rp;

	if (*path != '/') {
		if (strlen(path) >= size)
			goto erange;
		strcpy(result, path);
		goto finish;
	} else if (*base != '/' || !size) {
		errno = EINVAL;
		return (NULL);
	} else if (size == 1)
		goto erange;
	/*
	 * seek to branched point.
	 */
	branch = path;
	for (pp = path, bp = base; *pp && *bp && *pp == *bp; pp++, bp++)
		if (*pp == '/')
			branch = pp;
	if ((*pp == 0 || (*pp == '/' && *(pp + 1) == 0)) &&
	    (*bp == 0 || (*bp == '/' && *(bp + 1) == 0))) {
		rp = result;
		*rp++ = '.';
		if (*pp == '/' || *(pp - 1) == '/')
			*rp++ = '/';
		if (rp > endp)
			goto erange;
		*rp = 0;
		goto finish;
	}
	if ((*pp == 0 && *bp == '/') || (*pp == '/' && *bp == 0))
		branch = pp;
	/*
	 * up to root.
	 */
	rp = result;
	for (bp = base + (branch - path); *bp; bp++)
		if (*bp == '/' && *(bp + 1) != 0) {
			if (rp + 3 > endp)
				goto erange;
			*rp++ = '.';
			*rp++ = '.';
			*rp++ = '/';
		}
	if (rp > endp)
		goto erange;
	*rp = 0;
	/*
	 * down to leaf.
	 */
	if (*branch) {
		if (rp + strlen(branch + 1) > endp)
			goto erange;
		strcpy(rp, branch + 1);
	} else
		*--rp = 0;
finish:
	return result;
erange:
	errno = ERANGE;
	return (NULL);
}