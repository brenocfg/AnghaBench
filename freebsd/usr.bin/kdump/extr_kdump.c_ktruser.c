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
 scalar_t__ decimal ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ sysdecode_utrace (int /*<<< orphan*/ ,void*,int) ; 

void
ktruser(int len, void *p)
{
	unsigned char *cp;

	if (sysdecode_utrace(stdout, p, len)) {
		printf("\n");
		return;
	}

	printf("%d ", len);
	cp = p;
	while (len--)
		if (decimal)
			printf(" %d", *cp++);
		else
			printf(" %02x", *cp++);
	printf("\n");
}