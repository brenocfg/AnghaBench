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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  cmp_t ;

/* Variables and functions */
 scalar_t__ CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
insertionsort(u_char *a, size_t n, size_t size, cmp_t cmp)
{
	u_char *ai, *s, *t, *u, tmp;
	int i;

	for (ai = a+size; --n >= 1; ai += size)
		for (t = ai; t > a; t -= size) {
			u = t - size;
			if (CMP(u, t) <= 0)
				break;
			swap(u, t);
		}
}