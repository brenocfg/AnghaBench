#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  indices; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ UniqueIndices ;

/* Variables and functions */
 int /*<<< orphan*/  binarytree_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  indexarray_clear (int /*<<< orphan*/ *) ; 

void UniqueIndices_destroy(UniqueIndices* self) {
	binarytree_clear(&self->tree);
	indexarray_clear(&self->indices);
}