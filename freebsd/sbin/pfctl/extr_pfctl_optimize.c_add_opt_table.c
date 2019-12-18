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
struct pfctl {int opts; } ;
struct TYPE_5__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ a; } ;
struct TYPE_7__ {TYPE_2__ v; } ;
struct pf_rule_addr {TYPE_3__ addr; } ;
struct pf_opt_tbl {scalar_t__ pt_rulecount; int /*<<< orphan*/  pt_name; int /*<<< orphan*/  pt_nodes; TYPE_4__* pt_buf; } ;
struct node_tinit {int /*<<< orphan*/ * host; } ;
struct node_host {TYPE_3__ addr; int /*<<< orphan*/  af; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  node_host ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  pfrb_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PFRB_ADDRS ; 
 char* PF_OPT_TABLE_PREFIX ; 
 int PF_OPT_VERBOSE ; 
 int /*<<< orphan*/  SIMPLEQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_INSERT_TAIL (int /*<<< orphan*/ *,struct node_tinit*,int /*<<< orphan*/ ) ; 
 scalar_t__ TABLE_THRESHOLD ; 
 scalar_t__ append_addr_host (TYPE_4__*,struct node_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct node_host*,int) ; 
 int /*<<< orphan*/  memset (struct node_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
add_opt_table(struct pfctl *pf, struct pf_opt_tbl **tbl, sa_family_t af,
    struct pf_rule_addr *addr)
{
#ifdef OPT_DEBUG
	char buf[128];
#endif /* OPT_DEBUG */
	static int tablenum = 0;
	struct node_host node_host;

	if (*tbl == NULL) {
		if ((*tbl = calloc(1, sizeof(**tbl))) == NULL ||
		    ((*tbl)->pt_buf = calloc(1, sizeof(*(*tbl)->pt_buf))) ==
		    NULL)
			err(1, "calloc");
		(*tbl)->pt_buf->pfrb_type = PFRB_ADDRS;
		SIMPLEQ_INIT(&(*tbl)->pt_nodes);

		/* This is just a temporary table name */
		snprintf((*tbl)->pt_name, sizeof((*tbl)->pt_name), "%s%d",
		    PF_OPT_TABLE_PREFIX, tablenum++);
		DEBUG("creating table <%s>", (*tbl)->pt_name);
	}

	memset(&node_host, 0, sizeof(node_host));
	node_host.af = af;
	node_host.addr = addr->addr;

#ifdef OPT_DEBUG
	DEBUG("<%s> adding %s/%d", (*tbl)->pt_name, inet_ntop(af,
	    &node_host.addr.v.a.addr, buf, sizeof(buf)),
	    unmask(&node_host.addr.v.a.mask, af));
#endif /* OPT_DEBUG */

	if (append_addr_host((*tbl)->pt_buf, &node_host, 0, 0)) {
		warn("failed to add host");
		return (1);
	}
	if (pf->opts & PF_OPT_VERBOSE) {
		struct node_tinit *ti;

		if ((ti = calloc(1, sizeof(*ti))) == NULL)
			err(1, "malloc");
		if ((ti->host = malloc(sizeof(*ti->host))) == NULL)
			err(1, "malloc");
		memcpy(ti->host, &node_host, sizeof(*ti->host));
		SIMPLEQ_INSERT_TAIL(&(*tbl)->pt_nodes, ti, entries);
	}

	(*tbl)->pt_rulecount++;
	if ((*tbl)->pt_rulecount == TABLE_THRESHOLD)
		DEBUG("table <%s> now faster than skip steps", (*tbl)->pt_name);

	return (0);
}