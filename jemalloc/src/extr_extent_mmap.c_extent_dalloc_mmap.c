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
 int opt_retain ; 
 int /*<<< orphan*/  pages_unmap (void*,size_t) ; 

bool
extent_dalloc_mmap(void *addr, size_t size) {
	if (!opt_retain) {
		pages_unmap(addr, size);
	}
	return opt_retain;
}