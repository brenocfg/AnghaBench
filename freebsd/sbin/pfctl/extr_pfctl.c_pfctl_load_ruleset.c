#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pfctl {int opts; scalar_t__ optimize; TYPE_4__* anchor; } ;
struct pf_ruleset {TYPE_2__* rules; TYPE_4__* anchor; } ;
struct pf_rule {TYPE_3__* anchor; } ;
struct TYPE_8__ {char* name; } ;
struct TYPE_7__ {struct pf_ruleset ruleset; } ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {TYPE_1__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDENT (int,int) ; 
 scalar_t__ MAXPATHLEN ; 
 int PF_OPT_NOACTION ; 
 int PF_OPT_VERBOSE ; 
 int PF_RULESET_FILTER ; 
 struct pf_rule* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct pf_rule*) ; 
 int pfctl_load_rule (struct pfctl*,char*,struct pf_rule*,int) ; 
 int /*<<< orphan*/  pfctl_optimize_ruleset (struct pfctl*,struct pf_ruleset*) ; 
 int pfctl_ruleset_trans (struct pfctl*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 int strlen (char*) ; 

int
pfctl_load_ruleset(struct pfctl *pf, char *path, struct pf_ruleset *rs,
    int rs_num, int depth)
{
	struct pf_rule *r;
	int		error, len = strlen(path);
	int		brace = 0;

	pf->anchor = rs->anchor;

	if (path[0])
		snprintf(&path[len], MAXPATHLEN - len, "/%s", pf->anchor->name);
	else
		snprintf(&path[len], MAXPATHLEN - len, "%s", pf->anchor->name);

	if (depth) {
		if (TAILQ_FIRST(rs->rules[rs_num].active.ptr) != NULL) {
			brace++;
			if (pf->opts & PF_OPT_VERBOSE)
				printf(" {\n");
			if ((pf->opts & PF_OPT_NOACTION) == 0 &&
			    (error = pfctl_ruleset_trans(pf,
			    path, rs->anchor))) {
				printf("pfctl_load_rulesets: "
				    "pfctl_ruleset_trans %d\n", error);
				goto error;
			}
		} else if (pf->opts & PF_OPT_VERBOSE)
			printf("\n");

	}

	if (pf->optimize && rs_num == PF_RULESET_FILTER)
		pfctl_optimize_ruleset(pf, rs);

	while ((r = TAILQ_FIRST(rs->rules[rs_num].active.ptr)) != NULL) {
		TAILQ_REMOVE(rs->rules[rs_num].active.ptr, r, entries);
		if ((error = pfctl_load_rule(pf, path, r, depth)))
			goto error;
		if (r->anchor) {
			if ((error = pfctl_load_ruleset(pf, path,
			    &r->anchor->ruleset, rs_num, depth + 1)))
				goto error;
		} else if (pf->opts & PF_OPT_VERBOSE)
			printf("\n");
		free(r);
	}
	if (brace && pf->opts & PF_OPT_VERBOSE) {
		INDENT(depth - 1, (pf->opts & PF_OPT_VERBOSE));
		printf("}\n");
	}
	path[len] = '\0';
	return (0);

 error:
	path[len] = '\0';
	return (error);

}