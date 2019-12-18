#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int8_t ;
struct pfctl {TYPE_1__* anchor; } ;
struct pf_ruleset {TYPE_4__* rules; } ;
struct TYPE_12__ {int /*<<< orphan*/  list; } ;
struct pf_rule {TYPE_5__ rpool; TYPE_2__* anchor; int /*<<< orphan*/  action; } ;
struct TYPE_13__ {TYPE_2__* anchor; } ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_11__ {TYPE_3__ active; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  path; TYPE_7__ ruleset; } ;
struct TYPE_8__ {struct pf_ruleset ruleset; } ;

/* Variables and functions */
 size_t PF_RULESET_MAX ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ ,struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct pf_rule*,struct pf_rule*,int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 size_t pf_get_ruleset_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_init_ruleset (TYPE_7__*) ; 
 int /*<<< orphan*/  pfctl_move_pool (TYPE_5__*,TYPE_5__*) ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char const*,char) ; 

int
pfctl_add_rule(struct pfctl *pf, struct pf_rule *r, const char *anchor_call)
{
	u_int8_t		rs_num;
	struct pf_rule		*rule;
	struct pf_ruleset	*rs;
	char 			*p;

	rs_num = pf_get_ruleset_number(r->action);
	if (rs_num == PF_RULESET_MAX)
		errx(1, "Invalid rule type %d", r->action);

	rs = &pf->anchor->ruleset;

	if (anchor_call[0] && r->anchor == NULL) {
		/* 
		 * Don't make non-brace anchors part of the main anchor pool.
		 */
		if ((r->anchor = calloc(1, sizeof(*r->anchor))) == NULL)
			err(1, "pfctl_add_rule: calloc");
		
		pf_init_ruleset(&r->anchor->ruleset);
		r->anchor->ruleset.anchor = r->anchor;
		if (strlcpy(r->anchor->path, anchor_call,
		    sizeof(rule->anchor->path)) >= sizeof(rule->anchor->path))
			errx(1, "pfctl_add_rule: strlcpy");
		if ((p = strrchr(anchor_call, '/')) != NULL) {
			if (!strlen(p))
				err(1, "pfctl_add_rule: bad anchor name %s",
				    anchor_call);
		} else
			p = (char *)anchor_call;
		if (strlcpy(r->anchor->name, p,
		    sizeof(rule->anchor->name)) >= sizeof(rule->anchor->name))
			errx(1, "pfctl_add_rule: strlcpy");
	}

	if ((rule = calloc(1, sizeof(*rule))) == NULL)
		err(1, "calloc");
	bcopy(r, rule, sizeof(*rule));
	TAILQ_INIT(&rule->rpool.list);
	pfctl_move_pool(&r->rpool, &rule->rpool);

	TAILQ_INSERT_TAIL(rs->rules[rs_num].active.ptr, rule, entries);
	return (0);
}