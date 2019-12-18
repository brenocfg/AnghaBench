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
struct TYPE_2__ {int /*<<< orphan*/  (* to_attach ) (char*,int) ;} ;

/* Variables and functions */
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  thr_infpid (int /*<<< orphan*/ *) ; 
 scalar_t__ uw_thread_active ; 

__attribute__((used)) static void
uw_thread_attach (char *args, int from_tty)
{
  procfs_ops.to_attach (args, from_tty);
  if (uw_thread_active)
    thr_infpid (NULL);
}