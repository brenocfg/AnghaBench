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
 int /*<<< orphan*/  cnadd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_cninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_cnprobe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_consdev ; 

void
gdb_consinit(void)
{
	gdb_cnprobe(&gdb_consdev);
	gdb_cninit(&gdb_consdev);
	cnadd(&gdb_consdev);
}