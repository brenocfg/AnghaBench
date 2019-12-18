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
typedef  int /*<<< orphan*/  gdb_wince_len ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_WRITEPROCESSMEMORY ; 
 int getresult (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puthandle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putmemory (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpvoid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s ; 

__attribute__((used)) static int
write_process_memory (HANDLE h, LPCVOID where, LPCVOID buf, gdb_wince_len len, gdb_wince_len * nbytes)
{
  if (s < 0)
    return 1;
  puthandle ("WriteProcessMemory handle", GDB_WRITEPROCESSMEMORY, h);
  putpvoid ("WriteProcessMemory location", GDB_WRITEPROCESSMEMORY, where);
  putmemory ("WriteProcProcessMemory buf", GDB_WRITEPROCESSMEMORY, buf, len);

  return getresult ("WriteProcessMemory result", GDB_WRITEPROCESSMEMORY, nbytes, NULL);
}