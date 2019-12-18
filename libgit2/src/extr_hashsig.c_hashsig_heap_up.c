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
struct TYPE_3__ {scalar_t__ (* cmp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ hashsig_heap ;

/* Variables and functions */
 int HEAP_PARENT_OF (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hashsig_heap_up(hashsig_heap *h, int el)
{
	int parent_el = HEAP_PARENT_OF(el);

	while (el > 0 && h->cmp(&h->values[parent_el], &h->values[el], NULL) > 0) {
		hashsig_t t = h->values[el];
		h->values[el] = h->values[parent_el];
		h->values[parent_el] = t;

		el = parent_el;
		parent_el = HEAP_PARENT_OF(el);
	}
}