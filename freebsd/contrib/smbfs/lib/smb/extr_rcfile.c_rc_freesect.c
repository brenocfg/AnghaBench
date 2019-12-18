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
struct rcsection {struct rcsection* rs_name; int /*<<< orphan*/  rs_keys; } ;
struct rckey {int dummy; } ;
struct rcfile {int /*<<< orphan*/  rf_sect; } ;

/* Variables and functions */
 struct rckey* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct rckey* SLIST_NEXT (struct rckey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct rcsection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rcsection*) ; 
 int /*<<< orphan*/  rc_key_free (struct rckey*) ; 
 int /*<<< orphan*/  rcsection ; 
 int /*<<< orphan*/  rk_next ; 
 int /*<<< orphan*/  rs_next ; 

__attribute__((used)) static int
rc_freesect(struct rcfile *rcp, struct rcsection *rsp)
{
	struct rckey *p,*n;

	SLIST_REMOVE(&rcp->rf_sect, rsp, rcsection, rs_next);
	for(p = SLIST_FIRST(&rsp->rs_keys);p;) {
		n = p;
		p = SLIST_NEXT(p,rk_next);
		rc_key_free(n);
	}
	free(rsp->rs_name);
	free(rsp);
	return 0;
}