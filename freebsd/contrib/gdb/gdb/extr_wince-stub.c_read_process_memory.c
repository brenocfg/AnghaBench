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
typedef  scalar_t__ gdb_wince_result ;
typedef  scalar_t__ gdb_wince_len ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_READPROCESSMEMORY ; 
 scalar_t__ ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gethandle (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ getlen (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpvoid (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool (unsigned int) ; 
 int /*<<< orphan*/  putresult (char*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
read_process_memory (int s)
{
  HANDLE h = gethandle (L"ReadProcessMemory handle", s, GDB_READPROCESSMEMORY);
  LPVOID p = getpvoid (L"ReadProcessMemory base", s, GDB_READPROCESSMEMORY);
  gdb_wince_len len = getlen (L"ReadProcessMemory size", s, GDB_READPROCESSMEMORY);
  LPVOID buf = mempool ((unsigned int) len);
  DWORD outlen;
  gdb_wince_result res;

  outlen = 0;
  res = (gdb_wince_result) ReadProcessMemory (h, p, buf, len, &outlen);
  putresult (L"ReadProcessMemory data", res, s, GDB_READPROCESSMEMORY,
	     buf, (gdb_wince_len) outlen);
}