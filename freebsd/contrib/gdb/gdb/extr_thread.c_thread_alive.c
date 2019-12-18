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
struct thread_info {int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  target_thread_alive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thread_alive (struct thread_info *tp)
{
  if (PIDGET (tp->ptid) == -1)
    return 0;
  if (!target_thread_alive (tp->ptid))
    {
      tp->ptid = pid_to_ptid (-1);	/* Mark it as dead */
      return 0;
    }
  return 1;
}