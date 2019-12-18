#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t dwPageSize; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 size_t getpagesize () ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
os_page_detect(void) {
#ifdef _WIN32
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwPageSize;
#elif defined(__FreeBSD__)
	return getpagesize();
#else
	long result = sysconf(_SC_PAGESIZE);
	if (result == -1) {
		return LG_PAGE;
	}
	return (size_t)result;
#endif
}