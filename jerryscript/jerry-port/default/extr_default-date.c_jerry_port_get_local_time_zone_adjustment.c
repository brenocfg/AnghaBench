#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_gmtoff; } ;
struct TYPE_6__ {scalar_t__ QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_7__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int LONGLONG ;
typedef  TYPE_2__ FILETIME ;

/* Variables and functions */
 scalar_t__ FileTimeToSystemTime (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SystemTimeToFileTime (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ SystemTimeToTzSpecificLocalTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnixTimeToFileTime (int,TYPE_2__*) ; 
 int /*<<< orphan*/  _tzset () ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 

double jerry_port_get_local_time_zone_adjustment (double unix_ms,  /**< ms since unix epoch */
                                                  bool is_utc)  /**< is the time above in UTC? */
{
#ifdef HAVE_TM_GMTOFF
  struct tm tm;
  time_t now = (time_t) (unix_ms / 1000);
  localtime_r (&now, &tm);
  if (!is_utc)
  {
    now -= tm.tm_gmtoff;
    localtime_r (&now, &tm);
  }
  return ((double) tm.tm_gmtoff) * 1000;
#else /* !HAVE_TM_GMTOFF */
  (void) unix_ms;
  (void) is_utc;
#ifdef _WINDOWS
  FILETIME fileTime, localFileTime;
  SYSTEMTIME systemTime, localSystemTime;
  ULARGE_INTEGER time, localTime;

  _tzset ();
  UnixTimeToFileTime ((LONGLONG) (unix_ms / 1000), &fileTime);

  if (FileTimeToSystemTime (&fileTime, &systemTime)
      && SystemTimeToTzSpecificLocalTime (0, &systemTime, &localSystemTime)
      && SystemTimeToFileTime (&localSystemTime, &localFileTime))
  {
    time.LowPart = fileTime.dwLowDateTime;
    time.HighPart = fileTime.dwHighDateTime;
    localTime.LowPart = localFileTime.dwLowDateTime;
    localTime.HighPart = localFileTime.dwHighDateTime;
    return ((LONGLONG) localTime.QuadPart - (LONGLONG) time.QuadPart) / 10000;
  }
#endif /* _WINDOWS */
  return 0.0;
#endif /* HAVE_TM_GMTOFF */
}