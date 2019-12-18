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
typedef  int u_int16_t ;
struct ucred {int cr_uid; scalar_t__ cr_gid; } ;
struct rule {scalar_t__ r_protocol; int r_port; scalar_t__ r_idtype; scalar_t__ r_id; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PRIV_NETINET_RESERVEDPORT ; 
 scalar_t__ RULE_GID ; 
 scalar_t__ RULE_PROTO_TCP ; 
 scalar_t__ RULE_PROTO_UDP ; 
 scalar_t__ RULE_UID ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 struct rule* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct rule* TAILQ_NEXT (struct rule*,int /*<<< orphan*/ ) ; 
 scalar_t__ groupmember (scalar_t__,struct ucred*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int portacl_port_high ; 
 scalar_t__ portacl_suser_exempt ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_entries ; 
 int /*<<< orphan*/  rule_head ; 
 int /*<<< orphan*/  rule_mtx ; 

__attribute__((used)) static int
rules_check(struct ucred *cred, int family, int type, u_int16_t port)
{
	struct rule *rule;
	int error;

#if 0
	printf("Check requested for euid %d, family %d, type %d, port %d\n",
	    cred->cr_uid, family, type, port);
#endif

	if (port > portacl_port_high)
		return (0);

	error = EPERM;
	mtx_lock(&rule_mtx);
	for (rule = TAILQ_FIRST(&rule_head);
	    rule != NULL;
	    rule = TAILQ_NEXT(rule, r_entries)) {
		if (type == SOCK_DGRAM && rule->r_protocol != RULE_PROTO_UDP)
			continue;
		if (type == SOCK_STREAM && rule->r_protocol != RULE_PROTO_TCP)
			continue;
		if (port != rule->r_port)
			continue;
		if (rule->r_idtype == RULE_UID) {
			if (cred->cr_uid == rule->r_id) {
				error = 0;
				break;
			}
		} else if (rule->r_idtype == RULE_GID) {
			if (cred->cr_gid == rule->r_id) {
				error = 0;
				break;
			} else if (groupmember(rule->r_id, cred)) {
				error = 0;
				break;
			}
		} else
			panic("rules_check: unknown rule type %d",
			    rule->r_idtype);
	}
	mtx_unlock(&rule_mtx);

	if (error != 0 && portacl_suser_exempt != 0)
		error = priv_check_cred(cred, PRIV_NETINET_RESERVEDPORT);

	return (error);
}