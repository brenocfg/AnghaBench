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
typedef  int /*<<< orphan*/  PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_CREATEPROCESS ; 
 int getresult (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putdword (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putmemory (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  towide (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
create_process (LPSTR exec_file, LPSTR args, DWORD flags, PROCESS_INFORMATION * pi)
{
  gdb_wince_len len;
  LPWSTR buf;

  buf = towide (exec_file, &len);
  putmemory ("CreateProcess exec_file", GDB_CREATEPROCESS, buf, len);
  buf = towide (args, &len);
  putmemory ("CreateProcess args", GDB_CREATEPROCESS, buf, len);
  putdword ("CreateProcess flags", GDB_CREATEPROCESS, flags);
  return getresult ("CreateProcess result", GDB_CREATEPROCESS, pi, NULL);
}