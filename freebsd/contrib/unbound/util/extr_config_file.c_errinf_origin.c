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
struct sock_list {scalar_t__ len; int /*<<< orphan*/  addr; struct sock_list* next; } ;
struct module_qstate {TYPE_2__* env; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int val_log_level; int /*<<< orphan*/  log_servfail; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_to_str (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int strlen (char*) ; 

void errinf_origin(struct module_qstate* qstate, struct sock_list *origin)
{
	struct sock_list* p;
	if(qstate->env->cfg->val_log_level < 2 && !qstate->env->cfg->log_servfail)
		return;
	for(p=origin; p; p=p->next) {
		char buf[256];
		if(p == origin)
			snprintf(buf, sizeof(buf), "from ");
		else	snprintf(buf, sizeof(buf), "and ");
		if(p->len == 0)
			snprintf(buf+strlen(buf), sizeof(buf)-strlen(buf), 
				"cache");
		else 
			addr_to_str(&p->addr, p->len, buf+strlen(buf),
				sizeof(buf)-strlen(buf));
		errinf(qstate, buf);
	}
}