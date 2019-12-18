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
struct TYPE_3__ {scalar_t__ dwNumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 

int hc_get_processor_count ()
{
  int cnt = 0;

  #if defined (_WIN)

  SYSTEM_INFO info;

  GetSystemInfo (&info);

  cnt = (int) info.dwNumberOfProcessors;

  #else

  cnt = (int) sysconf (_SC_NPROCESSORS_ONLN);

  #endif

  return cnt;
}