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
 int /*<<< orphan*/  __je_bootstrap_free (void*) ; 

__attribute__((used)) static void
free_aligned(void *ptr)
{
	void *mem;
	uintptr_t x;

	if (ptr == NULL)
		return;

	x = (uintptr_t)ptr;
	x -= sizeof(void *);
	mem = *(void **)x;
	__je_bootstrap_free(mem);
}