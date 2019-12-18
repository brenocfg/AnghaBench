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
typedef  int /*<<< orphan*/  T_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_MODULE_MAIN ; 
 int /*<<< orphan*/  bsp_init () ; 
 int /*<<< orphan*/  cfw_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  pr_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xloop_init_from_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xloop_run (int /*<<< orphan*/ *) ; 

void main (void)
{
  T_QUEUE queue = bsp_init ();

  pr_info (LOG_MODULE_MAIN, "BSP init done");

  cfw_init (queue);
  pr_info (LOG_MODULE_MAIN, "CFW init done");

  xloop_init_from_queue (&loop, queue);

  xloop_run (&loop);
}