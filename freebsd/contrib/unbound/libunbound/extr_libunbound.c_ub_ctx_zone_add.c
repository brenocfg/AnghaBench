#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ub_ctx {TYPE_1__* local_zones; } ;
struct local_zone {int type; int /*<<< orphan*/  lock; } ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_SYNTAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zone_str2type (char const*,int*) ; 
 int /*<<< orphan*/  local_zones_add_zone (TYPE_1__*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int) ; 
 struct local_zone* local_zones_find (TYPE_1__*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_dname (char const*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int ub_ctx_finalize (struct ub_ctx*) ; 

int ub_ctx_zone_add(struct ub_ctx* ctx, const char *zone_name, 
	const char *zone_type)
{
	enum localzone_type t;
	struct local_zone* z;
	uint8_t* nm;
	int nmlabs;
	size_t nmlen;

	int res = ub_ctx_finalize(ctx);
	if (res) return res;

	if(!local_zone_str2type(zone_type, &t)) {
		return UB_SYNTAX;
	}

	if(!parse_dname(zone_name, &nm, &nmlen, &nmlabs)) {
		return UB_SYNTAX;
	}

	lock_rw_wrlock(&ctx->local_zones->lock);
	if((z=local_zones_find(ctx->local_zones, nm, nmlen, nmlabs, 
		LDNS_RR_CLASS_IN))) {
		/* already present in tree */
		lock_rw_wrlock(&z->lock);
		z->type = t; /* update type anyway */
		lock_rw_unlock(&z->lock);
		lock_rw_unlock(&ctx->local_zones->lock);
		free(nm);
		return UB_NOERROR;
	}
	if(!local_zones_add_zone(ctx->local_zones, nm, nmlen, nmlabs, 
		LDNS_RR_CLASS_IN, t)) {
		lock_rw_unlock(&ctx->local_zones->lock);
		return UB_NOMEM;
	}
	lock_rw_unlock(&ctx->local_zones->lock);
	return UB_NOERROR;
}