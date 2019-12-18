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
typedef  int /*<<< orphan*/  uint32_t ;
struct _citrus_iconv {int dummy; } ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int EBADF ; 
 scalar_t__ ISBADF (scalar_t__) ; 
 int _citrus_iconv_convert (struct _citrus_iconv*,char**,size_t*,char**,size_t*,int /*<<< orphan*/ ,size_t*) ; 
 int errno ; 

size_t
__bsd___iconv(iconv_t handle, char **in, size_t *szin, char **out,
    size_t *szout, uint32_t flags, size_t *invalids)
{
	size_t ret;
	int err;

	if (ISBADF(handle)) {
		errno = EBADF;
		return ((size_t)-1);
	}

	err = _citrus_iconv_convert((struct _citrus_iconv *)(void *)handle,
	    in, szin, out, szout, flags, &ret);
	if (invalids)
		*invalids = ret;
	if (err) {
		errno = err;
		ret = (size_t)-1;
	}

	return (ret);
}