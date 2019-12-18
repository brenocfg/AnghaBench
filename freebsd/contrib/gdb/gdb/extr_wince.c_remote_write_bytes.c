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
typedef  int gdb_wince_len ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_process_handle ; 
 int /*<<< orphan*/  write_process_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
remote_write_bytes (CORE_ADDR memaddr, char *myaddr, int len)
{
  gdb_wince_len nbytes;
  if (!write_process_memory (current_process_handle, (LPCVOID) memaddr,
			     (LPCVOID) myaddr, len, &nbytes))
    return -1;
  return nbytes;
}