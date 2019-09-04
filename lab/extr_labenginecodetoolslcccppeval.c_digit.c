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

int
digit(int i)
{
	if ('0'<=i && i<='9')
		i -= '0';
	else if ('a'<=i && i<='f')
		i -= 'a'-10;
	else if ('A'<=i && i<='F')
		i -= 'A'-10;
	else
		i = -1;
	return i;
}