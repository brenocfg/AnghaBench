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
typedef  int /*<<< orphan*/  zname ;
typedef  int /*<<< orphan*/  tpstr ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct dns_msg {int dummy; } ;
struct auth_zone {int fallback_enabled; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct auth_rrset {int /*<<< orphan*/  type; } ;
struct auth_data {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rrstr ;
typedef  int /*<<< orphan*/  qname ;
typedef  int /*<<< orphan*/  nname ;
typedef  int /*<<< orphan*/  cename ;

/* Variables and functions */
 scalar_t__ VERB_ALGO ; 
 int az_find_ce (struct auth_zone*,struct query_info*,struct auth_data*,int,struct auth_data**,struct auth_rrset**) ; 
 int /*<<< orphan*/  az_find_domain (struct auth_zone*,struct query_info*,int*,struct auth_data**) ; 
 int az_generate_answer_nonexistnode (struct auth_zone*,struct query_info*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*,struct auth_data*) ; 
 int az_generate_answer_with_node (struct auth_zone*,struct query_info*,struct regional*,struct dns_msg*,struct auth_data*) ; 
 int /*<<< orphan*/  log_info (char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 struct dns_msg* msg_create (struct regional*,struct query_info*) ; 
 int /*<<< orphan*/  sldns_wire2str_dname_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sldns_wire2str_type_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
auth_zone_generate_answer(struct auth_zone* z, struct query_info* qinfo,
	struct regional* region, struct dns_msg** msg, int* fallback)
{
	struct auth_data* node, *ce;
	struct auth_rrset* rrset;
	int node_exact, node_exists;
	/* does the zone want fallback in case of failure? */
	*fallback = z->fallback_enabled;
	if(!(*msg=msg_create(region, qinfo))) return 0;

	/* lookup if there is a matching domain name for the query */
	az_find_domain(z, qinfo, &node_exact, &node);

	/* see if node exists for generating answers from (i.e. not glue and
	 * obscured by NS or DNAME or NSEC3-only), and also return the
	 * closest-encloser from that, closest node that should be used
	 * to generate answers from that is above the query */
	node_exists = az_find_ce(z, qinfo, node, node_exact, &ce, &rrset);

	if(verbosity >= VERB_ALGO) {
		char zname[256], qname[256], nname[256], cename[256],
			tpstr[32], rrstr[32];
		sldns_wire2str_dname_buf(qinfo->qname, qinfo->qname_len, qname,
			sizeof(qname));
		sldns_wire2str_type_buf(qinfo->qtype, tpstr, sizeof(tpstr));
		sldns_wire2str_dname_buf(z->name, z->namelen, zname,
			sizeof(zname));
		if(node)
			sldns_wire2str_dname_buf(node->name, node->namelen,
				nname, sizeof(nname));
		else	snprintf(nname, sizeof(nname), "NULL");
		if(ce)
			sldns_wire2str_dname_buf(ce->name, ce->namelen,
				cename, sizeof(cename));
		else	snprintf(cename, sizeof(cename), "NULL");
		if(rrset) sldns_wire2str_type_buf(rrset->type, rrstr,
			sizeof(rrstr));
		else	snprintf(rrstr, sizeof(rrstr), "NULL");
		log_info("auth_zone %s query %s %s, domain %s %s %s, "
			"ce %s, rrset %s", zname, qname, tpstr, nname,
			(node_exact?"exact":"notexact"),
			(node_exists?"exist":"notexist"), cename, rrstr);
	}

	if(node_exists) {
		/* the node is fine, generate answer from node */
		return az_generate_answer_with_node(z, qinfo, region, *msg,
			node);
	}
	return az_generate_answer_nonexistnode(z, qinfo, region, *msg,
		ce, rrset, node);
}