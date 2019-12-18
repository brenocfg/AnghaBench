#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ func; } ;
struct drbg_state {TYPE_1__* d_ops; int /*<<< orphan*/ * jent; int /*<<< orphan*/  seed_work; TYPE_2__ random_ready; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* crypto_fini ) (struct drbg_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_rng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_random_ready_callback (TYPE_2__*) ; 
 int /*<<< orphan*/  drbg_dealloc_state (struct drbg_state*) ; 
 int /*<<< orphan*/  stub1 (struct drbg_state*) ; 

__attribute__((used)) static int drbg_uninstantiate(struct drbg_state *drbg)
{
	if (drbg->random_ready.func) {
		del_random_ready_callback(&drbg->random_ready);
		cancel_work_sync(&drbg->seed_work);
		crypto_free_rng(drbg->jent);
		drbg->jent = NULL;
	}

	if (drbg->d_ops)
		drbg->d_ops->crypto_fini(drbg);
	drbg_dealloc_state(drbg);
	/* no scrubbing of test_data -- this shall survive an uninstantiate */
	return 0;
}