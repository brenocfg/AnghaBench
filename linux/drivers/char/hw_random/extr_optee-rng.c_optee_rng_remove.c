#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  session_id; int /*<<< orphan*/  optee_rng; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__ pvt_data ; 
 int /*<<< orphan*/  tee_client_close_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_client_close_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int optee_rng_remove(struct device *dev)
{
	hwrng_unregister(&pvt_data.optee_rng);
	tee_client_close_session(pvt_data.ctx, pvt_data.session_id);
	tee_client_close_context(pvt_data.ctx);

	return 0;
}