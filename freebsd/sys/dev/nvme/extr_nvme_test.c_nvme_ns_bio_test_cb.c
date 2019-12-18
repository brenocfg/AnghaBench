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
struct mtx {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 int /*<<< orphan*/  wakeup (struct bio*) ; 

__attribute__((used)) static void
nvme_ns_bio_test_cb(struct bio *bio)
{
	struct mtx *mtx;

	mtx = mtx_pool_find(mtxpool_sleep, bio);
	mtx_lock(mtx);
	wakeup(bio);
	mtx_unlock(mtx);
}