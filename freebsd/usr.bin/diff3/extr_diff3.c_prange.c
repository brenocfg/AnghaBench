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
struct range {scalar_t__ to; scalar_t__ from; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
prange(struct range *rold)
{

	if (rold->to <= rold->from)
		printf("%da\n", rold->from - 1);
	else {
		printf("%d", rold->from);
		if (rold->to > rold->from+1)
			printf(",%d", rold->to - 1);
		printf("c\n");
	}
}