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
typedef  size_t u_int ;
struct unrhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPRINTF (char*,int) ; 
 int alloc_unr_specific (struct unrhdr*,size_t) ; 
 int /*<<< orphan*/  free_unr (struct unrhdr*,size_t) ; 

__attribute__((used)) static void
test_alloc_unr_specific(struct unrhdr *uh, u_int i, char a[])
{
	int j;

	j = alloc_unr_specific(uh, i);
	if (j == -1) {
		VPRINTF("F %u\n", i);
		a[i] = 0;
		free_unr(uh, i);
	} else {
		a[i] = 1;
		VPRINTF("A %d\n", j);
	}
}