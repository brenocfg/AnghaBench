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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *
rel2abs(const char *path, const char *base, char *result, const size_t size)
{
	const char *pp, *bp;
	/*
	 * endp points the last position which is safe in the result buffer.
	 */
	const char *endp = result + size - 1;
	char *rp;
	size_t length;

	if (*path == '/') {
		if (strlen(path) >= size)
			goto erange;
		strcpy(result, path);
		goto finish;
	} else if (*base != '/' || !size) {
		errno = EINVAL;
		return (NULL);
	} else if (size == 1)
		goto erange;

	length = strlen(base);

	if (!strcmp(path, ".") || !strcmp(path, "./")) {
		if (length >= size)
			goto erange;
		strcpy(result, base);
		/*
		 * rp points the last char.
		 */
		rp = result + length - 1;
		/*
		 * remove the last '/'.
		 */
		if (*rp == '/') {
			if (length > 1)
				*rp = 0;
		} else
			rp++;
		/* rp point NULL char */
		if (*++path == '/') {
			/*
			 * Append '/' to the tail of path name.
			 */
			*rp++ = '/';
			if (rp > endp)
				goto erange;
			*rp = 0;
		}
		goto finish;
	}
	bp = base + length;
	if (*(bp - 1) == '/')
		--bp;
	/*
	 * up to root.
	 */
	for (pp = path; *pp && *pp == '.'; ) {
		if (!strncmp(pp, "../", 3)) {
			pp += 3;
			while (bp > base && *--bp != '/')
				;
		} else if (!strncmp(pp, "./", 2)) {
			pp += 2;
		} else if (!strncmp(pp, "..\0", 3)) {
			pp += 2;
			while (bp > base && *--bp != '/')
				;
		} else
			break;
	}
	/*
	 * down to leaf.
	 */
	length = bp - base;
	if (length >= size)
		goto erange;
	strncpy(result, base, length);
	rp = result + length;
	if (*pp || *(pp - 1) == '/' || length == 0)
		*rp++ = '/';
	if (rp + strlen(pp) > endp)
		goto erange;
	strcpy(rp, pp);
finish:
	return result;
erange:
	errno = ERANGE;
	return (NULL);
}