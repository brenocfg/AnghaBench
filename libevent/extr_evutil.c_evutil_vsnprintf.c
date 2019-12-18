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
typedef  char* va_list ;
typedef  size_t __SGI_LIBC_NAMESPACE_QUALIFIER ;

/* Variables and functions */
 int _vscprintf (char const*,char*) ; 
 int _vsnprintf (char*,size_t,char const*,char*) ; 
 int vsnprintf (char*,size_t,char const*,char*) ; 

int
evutil_vsnprintf(char *buf, size_t buflen, const char *format, va_list ap)
{
	int r;
	if (!buflen)
		return 0;
#if defined(_MSC_VER) || defined(_WIN32)
	r = _vsnprintf(buf, buflen, format, ap);
	if (r < 0)
		r = _vscprintf(format, ap);
#elif defined(sgi)
	/* Make sure we always use the correct vsnprintf on IRIX */
	extern int      _xpg5_vsnprintf(char * __restrict,
		__SGI_LIBC_NAMESPACE_QUALIFIER size_t,
		const char * __restrict, /* va_list */ char *);

	r = _xpg5_vsnprintf(buf, buflen, format, ap);
#else
	r = vsnprintf(buf, buflen, format, ap);
#endif
	buf[buflen-1] = '\0';
	return r;
}