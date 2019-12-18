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
struct os_time {void* usec; void* sec; } ;
typedef  void* os_time_t ;
typedef  int ULONGLONG ;
struct TYPE_6__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_5__ {int QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ FILETIME ;

/* Variables and functions */
 int EPOCHFILETIME ; 
 int /*<<< orphan*/  GetSystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_2__*) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (int /*<<< orphan*/ *,TYPE_2__*) ; 

int os_get_time(struct os_time *t)
{
#define EPOCHFILETIME (116444736000000000ULL)
	FILETIME ft;
	LARGE_INTEGER li;
	ULONGLONG tt;

#ifdef _WIN32_WCE
	SYSTEMTIME st;

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
#else /* _WIN32_WCE */
	GetSystemTimeAsFileTime(&ft);
#endif /* _WIN32_WCE */
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	tt = (li.QuadPart - EPOCHFILETIME) / 10;
	t->sec = (os_time_t) (tt / 1000000);
	t->usec = (os_time_t) (tt % 1000000);

	return 0;
}