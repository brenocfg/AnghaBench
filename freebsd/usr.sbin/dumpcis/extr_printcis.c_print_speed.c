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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
print_speed(u_int i)
{
	if (i < 1000)
		printf("%u bits/sec", i);
	else if (i < 1000000)
		printf("%u kb/sec", i / 1000);
	else
		printf("%u Mb/sec", i / 1000000);
}