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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_READ_I ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int rs6000_ptrace32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rs6000_ptrace64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_word (CORE_ADDR from, int *to, int arch64)
{
  /* Retrieved values may be -1, so infer errors from errno. */
  errno = 0;

  if (arch64)
    *to = rs6000_ptrace64 (PT_READ_I, PIDGET (inferior_ptid), from, 0, NULL);
  else
    *to = rs6000_ptrace32 (PT_READ_I, PIDGET (inferior_ptid), (int *)(long) from,
                    0, NULL);

  return !errno;
}