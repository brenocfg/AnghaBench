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
typedef  size_t pszind_t ;
struct TYPE_3__ {int /*<<< orphan*/ * nbytes; int /*<<< orphan*/ * nextents; } ;
typedef  TYPE_1__ eset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eset_stats_add(eset_t *eset, pszind_t pind, size_t sz) {
	size_t cur = atomic_load_zu(&eset->nextents[pind], ATOMIC_RELAXED);
	atomic_store_zu(&eset->nextents[pind], cur + 1, ATOMIC_RELAXED);
	cur = atomic_load_zu(&eset->nbytes[pind], ATOMIC_RELAXED);
	atomic_store_zu(&eset->nbytes[pind], cur + sz, ATOMIC_RELAXED);
}