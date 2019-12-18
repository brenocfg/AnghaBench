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
 int /*<<< orphan*/  IDENT_WAIT ; 
 size_t OP_GET ; 
 size_t OP_GET_LEN ; 
 int /*<<< orphan*/  be_state ; 
 int /*<<< orphan*/  fgetlen_info ; 
 int /*<<< orphan*/  fgetval_info ; 
 int /*<<< orphan*/ ** ops ; 

void
fwctl_init(void)
{

	ops[OP_GET_LEN] = &fgetlen_info;
	ops[OP_GET]     = &fgetval_info;

	be_state = IDENT_WAIT;
}