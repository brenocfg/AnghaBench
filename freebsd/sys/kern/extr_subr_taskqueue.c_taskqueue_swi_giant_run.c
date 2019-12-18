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

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_swi_giant ; 

__attribute__((used)) static void
taskqueue_swi_giant_run(void *dummy)
{
	taskqueue_run(taskqueue_swi_giant);
}