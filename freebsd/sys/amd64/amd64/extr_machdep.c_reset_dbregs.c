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
 int /*<<< orphan*/  load_dr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr7 (int /*<<< orphan*/ ) ; 

void
reset_dbregs(void)
{

	load_dr7(0);	/* Turn off the control bits first */
	load_dr0(0);
	load_dr1(0);
	load_dr2(0);
	load_dr3(0);
	load_dr6(0);
}