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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUNCATE ; 
 int _vscprintf (char const*,int /*<<< orphan*/ ) ; 
 int _vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int _vsnprintf_s (char*,size_t,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int p_vsnprintf(char *buffer, size_t count, const char *format, va_list argptr)
{
#if defined(_MSC_VER)
	int len;

	if (count == 0)
		return _vscprintf(format, argptr);

	#if _MSC_VER >= 1500
	len = _vsnprintf_s(buffer, count, _TRUNCATE, format, argptr);
	#else
	len = _vsnprintf(buffer, count, format, argptr);
	#endif

	if (len < 0)
		return _vscprintf(format, argptr);

	return len;
#else /* MinGW */
	return vsnprintf(buffer, count, format, argptr);
#endif
}