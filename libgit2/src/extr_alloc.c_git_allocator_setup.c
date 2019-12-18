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
typedef  int /*<<< orphan*/  git_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  git__allocator ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int setup_default_allocator () ; 

int git_allocator_setup(git_allocator *allocator)
{
	if (!allocator)
		return setup_default_allocator();

	memcpy(&git__allocator, allocator, sizeof(*allocator));
	return 0;
}