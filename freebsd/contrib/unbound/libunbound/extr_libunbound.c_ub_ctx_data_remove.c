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
typedef  int /*<<< orphan*/  uint8_t ;
struct ub_ctx {int /*<<< orphan*/  local_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int UB_NOERROR ; 
 int UB_SYNTAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zones_del_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_dname (char const*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int ub_ctx_finalize (struct ub_ctx*) ; 

int ub_ctx_data_remove(struct ub_ctx* ctx, const char *data)
{
	uint8_t* nm;
	int nmlabs;
	size_t nmlen;
	int res = ub_ctx_finalize(ctx);
	if (res) return res;

	if(!parse_dname(data, &nm, &nmlen, &nmlabs)) 
		return UB_SYNTAX;

	local_zones_del_data(ctx->local_zones, nm, nmlen, nmlabs, 
		LDNS_RR_CLASS_IN);

	free(nm);
	return UB_NOERROR;
}