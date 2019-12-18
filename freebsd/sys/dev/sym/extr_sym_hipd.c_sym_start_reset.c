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
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 int /*<<< orphan*/  sym_reset_scsi_bus (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sym_start_reset(hcb_p np)
{
	(void) sym_reset_scsi_bus(np, 1);
}