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
typedef  int /*<<< orphan*/  uint32_t ;
struct octeon_device {int dummy; } ;
struct lio_soft_command {scalar_t__ ctxptr; } ;
struct lio_intrmod_context {int cond; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
lio_set_intrmod_callback(struct octeon_device *oct_dev, uint32_t status,
			 void *ptr)
{
	struct lio_soft_command		*sc = (struct lio_soft_command *)ptr;
	struct lio_intrmod_context	*ctx;

	ctx = (struct lio_intrmod_context *)sc->ctxptr;

	ctx->status = status;

	ctx->cond = 1;

	/*
	 * This barrier is required to be sure that the response has been
	 * written fully before waking up the handler
	 */
	wmb();
}