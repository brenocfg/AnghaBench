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
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

int str2mac(char *mac, char *str)
{
	unsigned int macf[6];
	int i;

	if (sscanf(str, "%x:%x:%x:%x:%x:%x",
		   &macf[0], &macf[1], &macf[2],
		   &macf[3], &macf[4], &macf[5]) != 6)
		return -1;

	for (i = 0; i < 6; i++)
		*mac++ = (char) macf[i];
	
	return 0;
}