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
typedef  int /*<<< orphan*/  res ;
typedef  int gdb_wince_result ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_THREADALIVE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethandle (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putresult (char*,int,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
thread_alive (int s)
{
  HANDLE h = gethandle (L"ThreadAlive handle", s, GDB_THREADALIVE);
  gdb_wince_result res;

  res = WaitForSingleObject (h, 0) == WAIT_OBJECT_0 ? 1 : 0;
  putresult (L"WriteProcessMemory data", res, s, GDB_THREADALIVE,
	     &res, sizeof (res));
}