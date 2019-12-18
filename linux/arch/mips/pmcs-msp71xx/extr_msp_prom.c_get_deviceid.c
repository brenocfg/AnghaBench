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
 int /*<<< orphan*/  DEVICEID ; 
 unsigned long* DEV_ID_REG ; 
 char* prom_getenv (int /*<<< orphan*/ ) ; 
 unsigned long str2hex (char*) ; 

unsigned long get_deviceid(void)
{
	char *deviceid = prom_getenv(DEVICEID);

	if (deviceid == NULL)
		return *DEV_ID_REG;
	else
		return str2hex(deviceid);
}