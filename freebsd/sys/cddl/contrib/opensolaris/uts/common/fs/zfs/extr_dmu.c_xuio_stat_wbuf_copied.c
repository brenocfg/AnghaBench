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
 int /*<<< orphan*/  XUIOSTAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xuiostat_wbuf_copied ; 

void
xuio_stat_wbuf_copied(void)
{
	XUIOSTAT_BUMP(xuiostat_wbuf_copied);
}