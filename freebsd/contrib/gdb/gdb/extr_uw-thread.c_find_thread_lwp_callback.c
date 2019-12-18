#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_info {TYPE_1__* private; int /*<<< orphan*/  ptid; } ;
struct TYPE_2__ {int lwpid; int /*<<< orphan*/  stable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISTID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_thread_lwp_callback (struct thread_info *tp, void *data)
{
  int lwpid = (int)data;

  if (!ISTID (tp->ptid))
    return 0;
  if (!tp->private->stable)
    return 0;
  if (lwpid != tp->private->lwpid)
    return 0;

  /* match */
  return 1;
}