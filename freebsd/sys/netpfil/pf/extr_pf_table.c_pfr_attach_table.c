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
typedef  int /*<<< orphan*/  tbl ;
struct pfr_table {struct pfr_table* pfrt_anchor; struct pfr_table* pfrt_name; } ;
struct pfr_ktable {int pfrkt_flags; int /*<<< orphan*/ * pfrkt_refcnt; struct pfr_ktable* pfrkt_root; } ;
struct pf_ruleset {struct pf_anchor* anchor; } ;
struct pf_anchor {char* path; } ;

/* Variables and functions */
 size_t PFR_REFCNT_RULE ; 
 int PFR_TFLAG_REFERENCED ; 
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 
 int /*<<< orphan*/  bzero (struct pfr_table*,int) ; 
 struct pfr_ktable* pfr_create_ktable (struct pfr_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfr_destroy_ktable (struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_insert_ktable (struct pfr_ktable*) ; 
 struct pfr_ktable* pfr_lookup_table (struct pfr_table*) ; 
 int /*<<< orphan*/  pfr_setflags_ktable (struct pfr_ktable*,int) ; 
 int /*<<< orphan*/  strlcpy (struct pfr_table*,char*,int) ; 
 int /*<<< orphan*/  time_second ; 

struct pfr_ktable *
pfr_attach_table(struct pf_ruleset *rs, char *name)
{
	struct pfr_ktable	*kt, *rt;
	struct pfr_table	 tbl;
	struct pf_anchor	*ac = rs->anchor;

	PF_RULES_WASSERT();

	bzero(&tbl, sizeof(tbl));
	strlcpy(tbl.pfrt_name, name, sizeof(tbl.pfrt_name));
	if (ac != NULL)
		strlcpy(tbl.pfrt_anchor, ac->path, sizeof(tbl.pfrt_anchor));
	kt = pfr_lookup_table(&tbl);
	if (kt == NULL) {
		kt = pfr_create_ktable(&tbl, time_second, 1);
		if (kt == NULL)
			return (NULL);
		if (ac != NULL) {
			bzero(tbl.pfrt_anchor, sizeof(tbl.pfrt_anchor));
			rt = pfr_lookup_table(&tbl);
			if (rt == NULL) {
				rt = pfr_create_ktable(&tbl, 0, 1);
				if (rt == NULL) {
					pfr_destroy_ktable(kt, 0);
					return (NULL);
				}
				pfr_insert_ktable(rt);
			}
			kt->pfrkt_root = rt;
		}
		pfr_insert_ktable(kt);
	}
	if (!kt->pfrkt_refcnt[PFR_REFCNT_RULE]++)
		pfr_setflags_ktable(kt, kt->pfrkt_flags|PFR_TFLAG_REFERENCED);
	return (kt);
}