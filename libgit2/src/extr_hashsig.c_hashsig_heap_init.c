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
struct TYPE_3__ {int /*<<< orphan*/  cmp; int /*<<< orphan*/  asize; scalar_t__ size; } ;
typedef  TYPE_1__ hashsig_heap ;
typedef  int /*<<< orphan*/  hashsig_cmp ;

/* Variables and functions */
 int /*<<< orphan*/  HASHSIG_HEAP_SIZE ; 

__attribute__((used)) static void hashsig_heap_init(hashsig_heap *h, hashsig_cmp cmp)
{
	h->size  = 0;
	h->asize = HASHSIG_HEAP_SIZE;
	h->cmp   = cmp;
}