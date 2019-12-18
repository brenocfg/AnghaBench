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
struct ub_ctx {int /*<<< orphan*/  local_zones; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int /*<<< orphan*/  local_zones_print (int /*<<< orphan*/ ) ; 
 int ub_ctx_finalize (struct ub_ctx*) ; 

int ub_ctx_print_local_zones(struct ub_ctx* ctx)
{   
	int res = ub_ctx_finalize(ctx);
	if (res) return res;

	local_zones_print(ctx->local_zones);

	return UB_NOERROR;
}