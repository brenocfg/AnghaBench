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
struct dh_ctx {int /*<<< orphan*/  p; int /*<<< orphan*/  xa; } ;
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 int mpi_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _compute_val(const struct dh_ctx *ctx, MPI base, MPI val)
{
	/* val = base^xa mod p */
	return mpi_powm(val, base, ctx->xa, ctx->p);
}