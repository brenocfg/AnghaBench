#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  __va_list ;
struct TYPE_5__ {unsigned char* _base; int _size; } ;
struct TYPE_6__ {int _flags; unsigned char* _p; int _w; TYPE_1__ _bf; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOVERFLOW ; 
 TYPE_2__ FAKE_FILE ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int __SALC ; 
 int __SSTR ; 
 int __SWR ; 
 int __vfwprintf (TYPE_2__*,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (int) ; 
 size_t mbsrtowcs_l (int*,char const**,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
vswprintf_l(wchar_t * __restrict s, size_t n, locale_t locale,
		const wchar_t * __restrict fmt, __va_list ap)
{
	static const mbstate_t initial;
	mbstate_t mbs;
	FILE f = FAKE_FILE;
	char *mbp;
	int ret, sverrno;
	size_t nwc;
	FIX_LOCALE(locale);

	if (n == 0) {
		errno = EINVAL;
		return (-1);
	}
	if (n - 1 > INT_MAX) {
		errno = EOVERFLOW;
		*s = L'\0';
		return (-1);
	}

	f._flags = __SWR | __SSTR | __SALC;
	f._bf._base = f._p = (unsigned char *)malloc(128);
	if (f._bf._base == NULL) {
		errno = ENOMEM;
		*s = L'\0';
		return (-1);
	}
	f._bf._size = f._w = 127;		/* Leave room for the NUL */
	ret = __vfwprintf(&f, locale, fmt, ap);
	if (ret < 0) {
		sverrno = errno;
		free(f._bf._base);
		errno = sverrno;
		*s = L'\0';
		return (-1);
	}
	*f._p = '\0';
	mbp = f._bf._base;
	/*
	 * XXX Undo the conversion from wide characters to multibyte that
	 * fputwc() did in __vfwprintf().
	 */
	mbs = initial;
	nwc = mbsrtowcs_l(s, (const char **)&mbp, n, &mbs, locale);
	free(f._bf._base);
	if (nwc == (size_t)-1) {
		errno = EILSEQ;
		*s = L'\0';
		return (-1);
	}
	if (nwc == n) {
		s[n - 1] = L'\0';
		errno = EOVERFLOW;
		return (-1);
	}

	return (ret);
}