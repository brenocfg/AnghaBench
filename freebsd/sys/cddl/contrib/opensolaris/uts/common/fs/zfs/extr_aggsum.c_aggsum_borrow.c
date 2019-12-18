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
typedef  int /*<<< orphan*/  uint64_t ;
struct aggsum_bucket {int /*<<< orphan*/  asc_lock; int /*<<< orphan*/  asc_borrowed; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  as_lock; int /*<<< orphan*/  as_lower_bound; int /*<<< orphan*/  as_upper_bound; } ;
typedef  TYPE_1__ aggsum_t ;

/* Variables and functions */
 int /*<<< orphan*/  aggsum_flush_bucket (TYPE_1__*,struct aggsum_bucket*) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aggsum_borrow(aggsum_t *as, int64_t delta, struct aggsum_bucket *asb)
{
	int64_t abs_delta = (delta < 0 ? -delta : delta);
	mutex_enter(&as->as_lock);
	mutex_enter(&asb->asc_lock);

	aggsum_flush_bucket(as, asb);

	atomic_add_64((volatile uint64_t *)&as->as_upper_bound, abs_delta);
	atomic_add_64((volatile uint64_t *)&as->as_lower_bound, -abs_delta);
	asb->asc_borrowed = abs_delta;

	mutex_exit(&asb->asc_lock);
	mutex_exit(&as->as_lock);
}