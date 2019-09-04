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
struct unpacked {scalar_t__ depth; int /*<<< orphan*/ * entry; scalar_t__ data; int /*<<< orphan*/ * index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (scalar_t__) ; 
 scalar_t__ SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_delta_index (int /*<<< orphan*/ *) ; 
 unsigned long sizeof_delta_index (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long free_unpacked(struct unpacked *n)
{
	unsigned long freed_mem = sizeof_delta_index(n->index);
	free_delta_index(n->index);
	n->index = NULL;
	if (n->data) {
		freed_mem += SIZE(n->entry);
		FREE_AND_NULL(n->data);
	}
	n->entry = NULL;
	n->depth = 0;
	return freed_mem;
}