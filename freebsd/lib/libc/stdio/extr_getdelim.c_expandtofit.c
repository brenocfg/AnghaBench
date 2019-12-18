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
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ SSIZE_MAX ; 
 int /*<<< orphan*/  errno ; 
 size_t p2roundup (size_t) ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static inline int
expandtofit(char ** __restrict linep, size_t len, size_t * __restrict capp)
{
	char *newline;
	size_t newcap;

	if (len > (size_t)SSIZE_MAX + 1) {
		errno = EOVERFLOW;
		return (-1);
	}
	if (len > *capp) {
		if (len == (size_t)SSIZE_MAX + 1)	/* avoid overflow */
			newcap = (size_t)SSIZE_MAX + 1;
		else
			newcap = p2roundup(len);
		newline = realloc(*linep, newcap);
		if (newline == NULL)
			return (-1);
		*capp = newcap;
		*linep = newline;
	}
	return (0);
}