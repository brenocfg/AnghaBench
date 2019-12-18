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
typedef  scalar_t__ uintmax_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 scalar_t__ strtoumax (char const*,char**,int) ; 

uintmax_t
strtounum(const char * __restrict np, uintmax_t minval, uintmax_t maxval,
    const char ** __restrict errpp)
{
	char *endp;
	uintmax_t ret;

	*errpp = NULL;
	if (minval > maxval) {
		errno = EINVAL;
		if (errpp != NULL)
			*errpp = "invalid";
		return (0);
	}
	errno = 0;
	ret = strtoumax(np, &endp, 10);
	if (endp == np || *endp != '\0') {
		errno = EINVAL;
		if (errpp != NULL)
			*errpp = "invalid";
		return (0);
	}
	if (ret < minval) {
		errno = ERANGE;
		if (errpp != NULL)
			*errpp = "too small";
		return (0);
	}
	if (errno == ERANGE || ret > maxval) {
		errno = ERANGE;
		if (errpp != NULL)
			*errpp = "too large";
		return (0);
	}
	return (ret);
}