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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ chancompar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
sort_channels(void *a, size_t n, size_t size)
{
	uint8_t *aa = a;
	uint8_t *ai, *t;

	KASSERT(n > 0, ("no channels"));
	for (ai = aa+size; --n >= 1; ai += size)
		for (t = ai; t > aa; t -= size) {
			uint8_t *u = t - size;
			if (chancompar(u, t) <= 0)
				break;
			swap(u, t, size);
		}
}