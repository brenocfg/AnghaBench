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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int bcm63xx_get_cpu_id () ; 
 int bcm63xx_get_cpu_rev () ; 
 char* board_get_name () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 

const char *get_system_type(void)
{
	static char buf[128];
	snprintf(buf, sizeof(buf), "bcm63xx/%s (0x%04x/0x%02X)",
		 board_get_name(),
		 bcm63xx_get_cpu_id(), bcm63xx_get_cpu_rev());
	return buf;
}