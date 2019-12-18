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
struct rwlock {int dummy; } ;
struct celockstate {struct rwlock** blp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_sort_vnodes (struct rwlock**,struct rwlock**) ; 
 int /*<<< orphan*/  rw_wlock (struct rwlock*) ; 

__attribute__((used)) static void
cache_lock_buckets_cel(struct celockstate *cel, struct rwlock *blp1,
    struct rwlock *blp2)
{

	MPASS(cel->blp[0] == NULL);
	MPASS(cel->blp[1] == NULL);

	cache_sort_vnodes(&blp1, &blp2);

	if (blp1 != NULL) {
		rw_wlock(blp1);
		cel->blp[0] = blp1;
	}
	rw_wlock(blp2);
	cel->blp[1] = blp2;
}