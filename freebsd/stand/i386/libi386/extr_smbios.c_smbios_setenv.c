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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  setenv (char const*,char const*,int) ; 
 char* smbios_getstring (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
smbios_setenv(const char *name, caddr_t addr, const int offset)
{
	const char*	val;

	val = smbios_getstring(addr, offset);
	if (val != NULL)
		setenv(name, val, 1);
}