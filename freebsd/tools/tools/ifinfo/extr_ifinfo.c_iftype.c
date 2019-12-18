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
 int NIFTYPES ; 
 char const** if_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char *
iftype(int type)
{
	static char buf[256];

	if (type <= 0 || type >= NIFTYPES) {
		sprintf(buf, "unknown type %d", type);
		return buf;
	}

	return if_types[type];
}