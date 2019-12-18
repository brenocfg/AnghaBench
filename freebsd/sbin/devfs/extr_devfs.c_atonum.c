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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 unsigned long UINT16_MAX ; 
 unsigned long strtoul (char const*,char**,int) ; 

int
atonum(const char *s, uint16_t *num)
{
	unsigned long ul;
	char *cp;

	ul = strtoul(s, &cp, 10);
	if (ul > UINT16_MAX || *cp != '\0')
		return (0);
	*num = (uint16_t)ul;
	return (1);
}