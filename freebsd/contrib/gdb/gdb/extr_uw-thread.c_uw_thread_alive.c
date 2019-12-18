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
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int (* to_thread_alive ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISTID (int /*<<< orphan*/ ) ; 
 TYPE_1__ base_ops ; 
 int in_thread_list (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uw_thread_alive (ptid_t ptid)
{
  if (!ISTID (ptid))
    return base_ops.to_thread_alive (ptid);

  /* If it's in the thread list, it's valid, because otherwise
     libthread_stub() would have deleted it. */
  return in_thread_list (ptid);
}