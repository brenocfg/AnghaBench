#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_6__ {int /*<<< orphan*/  dname; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_3__ rk; } ;
struct module_qstate {TYPE_2__* env; } ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {TYPE_1__* cfg; } ;
struct TYPE_4__ {int val_log_level; int /*<<< orphan*/  log_servfail; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wire2str_class_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sldns_wire2str_type_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 

void errinf_rrset(struct module_qstate* qstate, struct ub_packed_rrset_key *rr)
{
	char buf[1024];
	char dname[LDNS_MAX_DOMAINLEN+1];
	char t[16], c[16];
	if((qstate->env->cfg->val_log_level < 2 && !qstate->env->cfg->log_servfail) || !rr)
		return;
	sldns_wire2str_type_buf(ntohs(rr->rk.type), t, sizeof(t));
	sldns_wire2str_class_buf(ntohs(rr->rk.rrset_class), c, sizeof(c));
	dname_str(rr->rk.dname, dname);
	snprintf(buf, sizeof(buf), "for <%s %s %s>", dname, t, c);
	errinf(qstate, buf);
}