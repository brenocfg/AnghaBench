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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int DWORD ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MEM (char*) ; 
 int /*<<< orphan*/  FlushInstructionCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  WriteProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  current_process_handle ; 

int
child_xfer_memory (CORE_ADDR memaddr, char *our, int len,
		   int write, struct mem_attrib *mem,
		   struct target_ops *target)
{
  DWORD done = 0;
  if (write)
    {
      DEBUG_MEM (("gdb: write target memory, %d bytes at 0x%08lx\n",
		  len, (DWORD) memaddr));
      if (!WriteProcessMemory (current_process_handle, (LPVOID) memaddr, our,
			       len, &done))
	done = 0;
      FlushInstructionCache (current_process_handle, (LPCVOID) memaddr, len);
    }
  else
    {
      DEBUG_MEM (("gdb: read target memory, %d bytes at 0x%08lx\n",
		  len, (DWORD) memaddr));
      if (!ReadProcessMemory (current_process_handle, (LPCVOID) memaddr, our,
			      len, &done))
	done = 0;
    }
  return done;
}