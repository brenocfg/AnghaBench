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
 int /*<<< orphan*/  MILTER_STOP ; 
 int MI_SUCCESS ; 
 int /*<<< orphan*/  mi_stop_milters (int /*<<< orphan*/ ) ; 

int
smfi_stop()
{
	mi_stop_milters(MILTER_STOP);
	return MI_SUCCESS;
}