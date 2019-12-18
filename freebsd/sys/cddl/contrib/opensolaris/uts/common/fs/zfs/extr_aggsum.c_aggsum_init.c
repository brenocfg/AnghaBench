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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int as_numbuckets; TYPE_2__* as_buckets; int /*<<< orphan*/  as_lock; int /*<<< orphan*/  as_upper_bound; int /*<<< orphan*/  as_lower_bound; } ;
typedef  TYPE_1__ aggsum_t ;
typedef  int /*<<< orphan*/  aggsum_bucket_t ;
struct TYPE_6__ {int /*<<< orphan*/  asc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int boot_ncpus ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
aggsum_init(aggsum_t *as, uint64_t value)
{
	bzero(as, sizeof (*as));
	as->as_lower_bound = as->as_upper_bound = value;
	mutex_init(&as->as_lock, NULL, MUTEX_DEFAULT, NULL);
	as->as_numbuckets = boot_ncpus;
	as->as_buckets = kmem_zalloc(boot_ncpus * sizeof (aggsum_bucket_t),
	    KM_SLEEP);
	for (int i = 0; i < as->as_numbuckets; i++) {
		mutex_init(&as->as_buckets[i].asc_lock,
		    NULL, MUTEX_DEFAULT, NULL);
	}
}