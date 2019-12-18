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
 int /*<<< orphan*/  cur_src_end_addr ; 
 int /*<<< orphan*/  last_source_start_addr ; 
 int /*<<< orphan*/  process_linenos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
aix_process_linenos (void)
{
  /* process line numbers and enter them into line vector */
  process_linenos (last_source_start_addr, cur_src_end_addr);
}