#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoIndex_t ;
struct TYPE_6__ {scalar_t__ data; scalar_t__ last; } ;
struct TYPE_5__ {int /*<<< orphan*/  indices; TYPE_2__ tree; } ;
typedef  TYPE_1__ UniqueIndices ;

/* Variables and functions */
 int /*<<< orphan*/  UniqueIndices_find_or_insert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binarytree_extend (TYPE_2__*) ; 
 int /*<<< orphan*/  indexarray_push_back (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

picoIndex_t UniqueIndices_insert(UniqueIndices* self, picoIndex_t value) {
	if (self->tree.data == self->tree.last) {
		binarytree_extend(&self->tree);
		indexarray_push_back(&self->indices, value);
		return 0;
	}
	else
	{
		return UniqueIndices_find_or_insert(self, value);
	}
}