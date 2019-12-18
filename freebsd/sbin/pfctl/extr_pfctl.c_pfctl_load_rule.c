#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct pfioc_rule {int /*<<< orphan*/  anchor_call; int /*<<< orphan*/  rule; int /*<<< orphan*/  pool_ticket; int /*<<< orphan*/  anchor; int /*<<< orphan*/  ticket; } ;
struct TYPE_3__ {int /*<<< orphan*/  ticket; } ;
struct pfctl {int opts; int /*<<< orphan*/  dev; TYPE_1__ paddr; int /*<<< orphan*/  trans; } ;
struct pf_rule {int /*<<< orphan*/  rpool; TYPE_2__* anchor; int /*<<< orphan*/  af; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  pr ;
struct TYPE_4__ {char* name; char* path; scalar_t__ match; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCADDRULE ; 
 int /*<<< orphan*/  INDENT (int,int) ; 
 scalar_t__ MAXPATHLEN ; 
 int PF_OPT_NOACTION ; 
 int PF_OPT_NUMERIC ; 
 int PF_OPT_VERBOSE ; 
 int PF_OPT_VERBOSE2 ; 
 int /*<<< orphan*/  bzero (struct pfioc_rule*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_rule*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pf_rule*,int) ; 
 int /*<<< orphan*/  pf_get_ruleset_number (int /*<<< orphan*/ ) ; 
 scalar_t__ pfctl_add_pool (struct pfctl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfctl_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfctl_get_ticket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_rule (struct pf_rule*,char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 

int
pfctl_load_rule(struct pfctl *pf, char *path, struct pf_rule *r, int depth)
{
	u_int8_t		rs_num = pf_get_ruleset_number(r->action);
	char			*name;
	struct pfioc_rule	pr;
	int			len = strlen(path);

	bzero(&pr, sizeof(pr));
	/* set up anchor before adding to path for anchor_call */
	if ((pf->opts & PF_OPT_NOACTION) == 0)
		pr.ticket = pfctl_get_ticket(pf->trans, rs_num, path);
	if (strlcpy(pr.anchor, path, sizeof(pr.anchor)) >= sizeof(pr.anchor))
		errx(1, "pfctl_load_rule: strlcpy");

	if (r->anchor) {
		if (r->anchor->match) {
			if (path[0])
				snprintf(&path[len], MAXPATHLEN - len,
				    "/%s", r->anchor->name);
			else
				snprintf(&path[len], MAXPATHLEN - len,
				    "%s", r->anchor->name);
			name = r->anchor->name;
		} else
			name = r->anchor->path;
	} else
		name = "";

	if ((pf->opts & PF_OPT_NOACTION) == 0) {
		if (pfctl_add_pool(pf, &r->rpool, r->af))
			return (1);
		pr.pool_ticket = pf->paddr.ticket;
		memcpy(&pr.rule, r, sizeof(pr.rule));
		if (r->anchor && strlcpy(pr.anchor_call, name,
		    sizeof(pr.anchor_call)) >= sizeof(pr.anchor_call))
			errx(1, "pfctl_load_rule: strlcpy");
		if (ioctl(pf->dev, DIOCADDRULE, &pr))
			err(1, "DIOCADDRULE");
	}

	if (pf->opts & PF_OPT_VERBOSE) {
		INDENT(depth, !(pf->opts & PF_OPT_VERBOSE2));
		print_rule(r, r->anchor ? r->anchor->name : "",
		    pf->opts & PF_OPT_VERBOSE2,
		    pf->opts & PF_OPT_NUMERIC);
	}
	path[len] = '\0';
	pfctl_clear_pool(&r->rpool);
	return (0);
}