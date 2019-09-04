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
typedef  int /*<<< orphan*/  hashsig_t ;
struct TYPE_3__ {int size; scalar_t__ (* cmp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ hashsig_heap ;

/* Variables and functions */
 int HEAP_LCHILD_OF (int) ; 
 int HEAP_RCHILD_OF (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hashsig_heap_down(hashsig_heap *h, int el)
{
	hashsig_t v, lv, rv;

	/* 'el < h->size / 2' tests if el is bottom row of heap */

	while (el < h->size / 2) {
		int lel = HEAP_LCHILD_OF(el), rel = HEAP_RCHILD_OF(el), swapel;

		v  = h->values[el];
		lv = h->values[lel];
		rv = h->values[rel];

		if (h->cmp(&v, &lv, NULL) < 0 && h->cmp(&v, &rv, NULL) < 0)
			break;

		swapel = (h->cmp(&lv, &rv, NULL) < 0) ? lel : rel;

		h->values[el] = h->values[swapel];
		h->values[swapel] = v;

		el = swapel;
	}
}