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
typedef  char uint32_t ;

/* Variables and functions */
 int strlen (char*) ; 

int
str2sig(char *arg, uint32_t *sig)
{
	if (strlen(arg) != 4)
		return -1;

	*sig = arg[0] | (arg[1] << 8) | (arg[2] << 16) | (arg[3] << 24);

	return 0;
}