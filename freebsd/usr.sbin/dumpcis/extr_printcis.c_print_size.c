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
print_size(u_int i)
{
	if (i < 1024)
		printf("%ubits", i);
	else if (i < 1024*1024)
		printf("%ukb", i / 1024);
	else
		printf("%uMb", i / (1024*1024));
}