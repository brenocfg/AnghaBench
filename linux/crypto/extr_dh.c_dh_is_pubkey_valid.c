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
struct dh_ctx {int /*<<< orphan*/  p; scalar_t__ q; } ;
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  mpi_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ mpi_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpi_cmp_ui (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ ) ; 
 int mpi_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dh_is_pubkey_valid(struct dh_ctx *ctx, MPI y)
{
	if (unlikely(!ctx->p))
		return -EINVAL;

	/*
	 * Step 1: Verify that 2 <= y <= p - 2.
	 *
	 * The upper limit check is actually y < p instead of y < p - 1
	 * as the mpi_sub_ui function is yet missing.
	 */
	if (mpi_cmp_ui(y, 1) < 1 || mpi_cmp(y, ctx->p) >= 0)
		return -EINVAL;

	/* Step 2: Verify that 1 = y^q mod p */
	if (ctx->q) {
		MPI val = mpi_alloc(0);
		int ret;

		if (!val)
			return -ENOMEM;

		ret = mpi_powm(val, y, ctx->q, ctx->p);

		if (ret) {
			mpi_free(val);
			return ret;
		}

		ret = mpi_cmp_ui(val, 1);

		mpi_free(val);

		if (ret != 0)
			return -EINVAL;
	}

	return 0;
}