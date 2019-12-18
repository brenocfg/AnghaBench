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
 int /*<<< orphan*/  BIOS_CALL_CONSOLE_WRITE ; 
 int /*<<< orphan*/  sh_bios_call (int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sh_bios_console_write(const char *buf, unsigned int len)
{
	sh_bios_call(BIOS_CALL_CONSOLE_WRITE, (long)buf, (long)len, 0, 0);
}