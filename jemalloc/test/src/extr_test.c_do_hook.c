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
 int NUM_REENTRANT_ALLOCS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (size_t) ; 

__attribute__((used)) static void
do_hook(bool *hook_ran, void (**hook)()) {
	*hook_ran = true;
	*hook = NULL;

	size_t alloc_size = 1;
	for (int i = 0; i < NUM_REENTRANT_ALLOCS; i++) {
		free(malloc(alloc_size));
		alloc_size *= 2;
	}
}