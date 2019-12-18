#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__* sin_zero; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

void
print_addr(struct sockaddr_in addr)
{
	int i;

	printf("addr = %lx, port = %o, family = %o zero = ",
		(u_long)addr.sin_addr.s_addr, addr.sin_port, addr.sin_family);
	for (i = 0; i<8;i++)
	printf("%o ", (int)addr.sin_zero[i]);
	putchar('\n');
}