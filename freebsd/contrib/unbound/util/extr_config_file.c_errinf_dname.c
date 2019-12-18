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
typedef  int /*<<< orphan*/  uint8_t ;
struct module_qstate {TYPE_2__* env; } ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int val_log_level; int /*<<< orphan*/  log_servfail; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 

void errinf_dname(struct module_qstate* qstate, const char* str, uint8_t* dname)
{
	char b[1024];
	char buf[LDNS_MAX_DOMAINLEN+1];
	if((qstate->env->cfg->val_log_level < 2 && !qstate->env->cfg->log_servfail) || !str || !dname)
		return;
	dname_str(dname, buf);
	snprintf(b, sizeof(b), "%s %s", str, buf);
	errinf(qstate, b);
}