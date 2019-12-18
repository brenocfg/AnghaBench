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
typedef  scalar_t__ phandle ;

/* Variables and functions */
 scalar_t__ ldom_domaining_enabled ; 
 int /*<<< orphan*/  ldom_set_var (char const*,char*) ; 
 int /*<<< orphan*/  p1275_cmd_direct (unsigned long*) ; 

int
prom_setprop(phandle node, const char *pname, char *value, int size)
{
	unsigned long args[8];

	if (size == 0)
		return 0;
	if ((pname == 0) || (value == 0))
		return 0;
	
#ifdef CONFIG_SUN_LDOMS
	if (ldom_domaining_enabled) {
		ldom_set_var(pname, value);
		return 0;
	}
#endif
	args[0] = (unsigned long) "setprop";
	args[1] = 4;
	args[2] = 1;
	args[3] = (unsigned int) node;
	args[4] = (unsigned long) pname;
	args[5] = (unsigned long) value;
	args[6] = size;
	args[7] = (unsigned long) -1;

	p1275_cmd_direct(args);

	return (int) args[7];
}