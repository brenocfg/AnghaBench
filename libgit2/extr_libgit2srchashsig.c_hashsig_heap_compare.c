#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* cmp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int size; int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ hashsig_heap ;

/* Variables and functions */
 int HASHSIG_SCALE ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hashsig_heap_compare(const hashsig_heap *a, const hashsig_heap *b)
{
	int matches = 0, i, j, cmp;

	assert(a->cmp == b->cmp);

	/* hash heaps are sorted - just look for overlap vs total */

	for (i = 0, j = 0; i < a->size && j < b->size; ) {
		cmp = a->cmp(&a->values[i], &b->values[j], NULL);

		if (cmp < 0)
			++i;
		else if (cmp > 0)
			++j;
		else {
			++i; ++j; ++matches;
		}
	}

	return HASHSIG_SCALE * (matches * 2) / (a->size + b->size);
}