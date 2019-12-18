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
typedef  int /*<<< orphan*/  gdb_wince_result ;
typedef  scalar_t__ gdb_wince_len ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_WRITEPROCESSMEMORY ; 
 int /*<<< orphan*/  WriteProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gethandle (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmemory (char*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  getpvoid (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putresult (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
write_process_memory (int s)
{
  HANDLE h = gethandle (L"WriteProcessMemory handle", s, GDB_WRITEPROCESSMEMORY);
  LPVOID p = getpvoid (L"WriteProcessMemory base", s, GDB_WRITEPROCESSMEMORY);
  gdb_wince_len len;
  LPVOID buf = getmemory (L"WriteProcessMemory buf", s, GDB_WRITEPROCESSMEMORY, &len);
  DWORD outlen;
  gdb_wince_result res;

  outlen = 0;
  res = WriteProcessMemory (h, p, buf, (DWORD) len, &outlen);
  putresult (L"WriteProcessMemory data", res, s, GDB_WRITEPROCESSMEMORY,
	     (gdb_wince_len *) & outlen, sizeof (gdb_wince_len));
}