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
struct rcsection {int dummy; } ;
struct rcfile {struct rcfile* rf_name; int /*<<< orphan*/  rf_sect; int /*<<< orphan*/  rf_f; } ;

/* Variables and functions */
 struct rcsection* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct rcsection* SLIST_NEXT (struct rcsection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct rcfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rcfile*) ; 
 int /*<<< orphan*/  pf_head ; 
 int /*<<< orphan*/  rc_freesect (struct rcfile*,struct rcsection*) ; 
 int /*<<< orphan*/  rcfile ; 
 int /*<<< orphan*/  rf_next ; 
 int /*<<< orphan*/  rs_next ; 

int
rc_close(struct rcfile *rcp)
{
	struct rcsection *p, *n;

	fclose(rcp->rf_f);
	for(p = SLIST_FIRST(&rcp->rf_sect); p;) {
		n = p;
		p = SLIST_NEXT(p,rs_next);
		rc_freesect(rcp, n);
	}
	free(rcp->rf_name);
	SLIST_REMOVE(&pf_head, rcp, rcfile, rf_next);
	free(rcp);
	return 0;
}