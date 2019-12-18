#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_2__ {int /*<<< orphan*/  qname; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; } ;
struct module_qstate {struct config_strlist* errinf; TYPE_1__ qinfo; } ;
struct config_strlist {char* str; struct config_strlist* next; } ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  sldns_wire2str_class_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sldns_wire2str_type_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 

char* errinf_to_str_servfail(struct module_qstate* qstate)
{
	char buf[20480];
	char* p = buf;
	size_t left = sizeof(buf);
	struct config_strlist* s;
	char dname[LDNS_MAX_DOMAINLEN+1];
	char t[16], c[16];
	sldns_wire2str_type_buf(qstate->qinfo.qtype, t, sizeof(t));
	sldns_wire2str_class_buf(qstate->qinfo.qclass, c, sizeof(c));
	dname_str(qstate->qinfo.qname, dname);
	snprintf(p, left, "SERVFAIL <%s %s %s>:", dname, t, c);
	left -= strlen(p); p += strlen(p);
	if(!qstate->errinf)
		snprintf(p, left, " misc failure");
	else for(s=qstate->errinf; s; s=s->next) {
		snprintf(p, left, " %s", s->str);
		left -= strlen(p); p += strlen(p);
	}
	p = strdup(buf);
	if(!p)
		log_err("malloc failure in errinf_to_str");
	return p;
}