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
typedef  int u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int* tcpflags ; 

void
print_flags(u_int8_t f)
{
	int	i;

	for (i = 0; tcpflags[i]; ++i)
		if (f & (1 << i))
			printf("%c", tcpflags[i]);
}