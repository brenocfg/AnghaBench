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
struct optee_rng_private {int /*<<< orphan*/  entropy_shm_pool; } ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tee_shm_free (int /*<<< orphan*/ ) ; 
 struct optee_rng_private* to_optee_rng_private (struct hwrng*) ; 

__attribute__((used)) static void optee_rng_cleanup(struct hwrng *rng)
{
	struct optee_rng_private *pvt_data = to_optee_rng_private(rng);

	tee_shm_free(pvt_data->entropy_shm_pool);
}