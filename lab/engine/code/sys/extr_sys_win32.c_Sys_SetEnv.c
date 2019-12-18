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
 int /*<<< orphan*/  _putenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char const*,...) ; 

void Sys_SetEnv(const char *name, const char *value)
{
	if(value)
		_putenv(va("%s=%s", name, value));
	else
		_putenv(va("%s=", name));
}