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
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  __va_list ;
struct TYPE_5__ {unsigned char* _base; size_t _size; } ;
struct TYPE_6__ {int _flags; unsigned char* _p; size_t _w; TYPE_1__ _bf; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 TYPE_2__ FAKE_FILE ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int __SSTR ; 
 int __SWR ; 
 int __vfprintf (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
vsnprintf_l(char * __restrict str, size_t n, locale_t locale, 
		const char * __restrict fmt, __va_list ap)
{
	size_t on;
	int ret;
	char dummy[2];
	FILE f = FAKE_FILE;
	FIX_LOCALE(locale);

	on = n;
	if (n != 0)
		n--;
	if (n > INT_MAX) {
		errno = EOVERFLOW;
		*str = '\0';
		return (EOF);
	}
	/* Stdio internals do not deal correctly with zero length buffer */
	if (n == 0) {
		if (on > 0)
	  		*str = '\0';
		str = dummy;
		n = 1;
	}
	f._flags = __SWR | __SSTR;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._w = n;
	ret = __vfprintf(&f, locale, fmt, ap);
	if (on > 0)
		*f._p = '\0';
	return (ret);
}