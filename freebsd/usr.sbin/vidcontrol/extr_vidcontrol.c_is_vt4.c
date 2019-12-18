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
typedef  int /*<<< orphan*/  vty_name ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_vt4(void)
{
	char vty_name[4] = "";
	size_t len = sizeof(vty_name);

	if (sysctlbyname("kern.vty", vty_name, &len, NULL, 0) != 0)
		return (0);
	return (strcmp(vty_name, "vt") == 0);
}