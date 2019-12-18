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
 int /*<<< orphan*/  all_threads ; 
 int /*<<< orphan*/  fbsd_kill_one_process ; 
 int /*<<< orphan*/  for_each_inferior (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fbsd_kill (void)
{
  for_each_inferior (&all_threads, fbsd_kill_one_process);
}