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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int ENOENT ; 
 int errno ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 scalar_t__ nls_toext ; 
 scalar_t__ nls_toloc ; 

int
nls_setrecode(const char *local, const char *external)
{
#ifdef HAVE_ICONV
	iconv_t icd;

	if (nls_toext)
		iconv_close(nls_toext);
	if (nls_toloc)
		iconv_close(nls_toloc);
	nls_toext = nls_toloc = (iconv_t)0;
	icd = iconv_open(external, local);
	if (icd == (iconv_t)-1)
		return errno;
	nls_toext = icd;
	icd = iconv_open(local, external);
	if (icd == (iconv_t)-1) {
		iconv_close(nls_toext);
		nls_toext = (iconv_t)0;
		return errno;
	}
	nls_toloc = icd;
	return 0;
#else
	return ENOENT;
#endif
}