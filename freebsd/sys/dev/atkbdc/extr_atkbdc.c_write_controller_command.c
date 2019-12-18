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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_while_controller_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_command (int /*<<< orphan*/ ,int) ; 

int
write_controller_command(KBDC p, int c)
{
    if (!wait_while_controller_busy(kbdcp(p)))
	return FALSE;
    write_command(kbdcp(p), c);
    return TRUE;
}