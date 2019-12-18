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
 int /*<<< orphan*/  GIT_UNUSED (void**) ; 
 int /*<<< orphan*/  git__free (void*) ; 

__attribute__((used)) static int paths_on_dup(void **old, void *new)
{
	GIT_UNUSED(old);
	git__free(new);
	return -1;
}