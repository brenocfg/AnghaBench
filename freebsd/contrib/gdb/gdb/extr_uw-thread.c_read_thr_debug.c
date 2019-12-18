#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_debug {int dummy; } ;
struct TYPE_3__ {int (* to_xfer_memory ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_1__ base_ops ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  thr_debug_addr ; 

__attribute__((used)) static int
read_thr_debug (struct thread_debug *debugp)
{
  return base_ops.to_xfer_memory (thr_debug_addr, (char *)debugp,
				  sizeof (*debugp), 0, NULL, &base_ops);
}