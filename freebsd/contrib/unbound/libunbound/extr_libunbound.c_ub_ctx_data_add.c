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
 int UB_NOMEM ; 
 int local_zones_add_RR (int /*<<< orphan*/ ,char const*) ; 
 int ub_ctx_finalize (struct ub_ctx*) ; 

int ub_ctx_data_add(struct ub_ctx* ctx, const char *data)
{
	int res = ub_ctx_finalize(ctx);
	if (res) return res;

	res = local_zones_add_RR(ctx->local_zones, data);
	return (!res) ? UB_NOMEM : UB_NOERROR;
}