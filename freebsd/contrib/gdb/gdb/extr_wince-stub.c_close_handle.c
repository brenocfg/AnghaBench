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
typedef  scalar_t__ gdb_wince_result ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GDB_CLOSEHANDLE ; 
 int /*<<< orphan*/  gethandle (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putresult (char*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
close_handle (int s)
{
  gdb_wince_result res;
  HANDLE h = gethandle (L"CloseHandle handle", s, GDB_CLOSEHANDLE);
  res = (gdb_wince_result) CloseHandle (h);
  putresult (L"CloseHandle result", res, s, GDB_CLOSEHANDLE, &res, sizeof (res));
}