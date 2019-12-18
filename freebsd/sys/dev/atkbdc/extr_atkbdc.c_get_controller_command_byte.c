#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int command_byte; int /*<<< orphan*/  kbd; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  KBDC_GET_COMMAND_BYTE ; 
 int /*<<< orphan*/  emptyq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int read_controller_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
get_controller_command_byte(KBDC p)
{
    if (kbdcp(p)->command_byte != -1)
	return kbdcp(p)->command_byte;
    if (!write_controller_command(p, KBDC_GET_COMMAND_BYTE))
	return -1;
    emptyq(&kbdcp(p)->kbd);
    kbdcp(p)->command_byte = read_controller_data(p);
    return kbdcp(p)->command_byte;
}