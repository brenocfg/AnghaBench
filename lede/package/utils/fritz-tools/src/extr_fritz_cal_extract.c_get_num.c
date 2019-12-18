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
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int get_num(char *str)
{
	if (!strncmp("0x", str, 2))
		return strtoul(str+2, NULL, 16);
	else
		return strtoul(str, NULL, 10);
}