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
typedef  int /*<<< orphan*/  git_pool_page ;

/* Variables and functions */
 scalar_t__ git__page_size (size_t*) ; 

size_t git_pool__system_page_size(void)
{
	static size_t size = 0;

	if (!size) {
		size_t page_size;
		if (git__page_size(&page_size) < 0)
			page_size = 4096;
		/* allow space for malloc overhead */
		size = (page_size - (2 * sizeof(void *)) - sizeof(git_pool_page));
	}

	return size;
}