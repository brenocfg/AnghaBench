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
 char* mt_density_name (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static const char *
denstostring(int d)
{
	static char buf[20];
	const char *name = mt_density_name(d);

	if (name == NULL)
		sprintf(buf, "0x%02x", d);
	else 
		sprintf(buf, "0x%02x:%s", d, name);
	return buf;
}