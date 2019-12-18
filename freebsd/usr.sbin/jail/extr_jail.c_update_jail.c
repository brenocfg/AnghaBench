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
struct jailparam {int dummy; } ;
struct cfjail {int njp; int /*<<< orphan*/ * intparams; struct jailparam* jp; int /*<<< orphan*/  jid; } ;

/* Variables and functions */
 size_t IP_ALLOW_DYING ; 
 int JAIL_DYING ; 
 int JAIL_UPDATE ; 
 int /*<<< orphan*/  JP_RDTUN (struct jailparam*) ; 
 struct jailparam* alloca (int) ; 
 scalar_t__ bool_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failed (struct cfjail*) ; 
 int /*<<< orphan*/  jail_errmsg ; 
 int /*<<< orphan*/  jail_warnx (struct cfjail*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jailparam_free (struct jailparam*,int) ; 
 scalar_t__ jailparam_import_raw (struct jailparam*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ jailparam_init (struct jailparam*,char*) ; 
 int jailparam_set_note (struct cfjail*,struct jailparam*,int,int) ; 

__attribute__((used)) static int
update_jail(struct cfjail *j)
{
	struct jailparam *jp, *setparams, *sjp;
	int ns, jid;

	ns = 0;
	for (jp = j->jp; jp < j->jp + j->njp; jp++)
		if (!JP_RDTUN(jp))
			ns++;
	if (ns == 0)
		return 0;
	sjp = setparams = alloca(++ns * sizeof(struct jailparam));
	if (jailparam_init(sjp, "jid") < 0 ||
	    jailparam_import_raw(sjp, &j->jid, sizeof j->jid) < 0) {
		jail_warnx(j, "%s", jail_errmsg);
		failed(j);
		return -1;
	}
	for (jp = j->jp; jp < j->jp + j->njp; jp++)
		if (!JP_RDTUN(jp))
			*++sjp = *jp;

	jid = jailparam_set_note(j, setparams, ns,
	    bool_param(j->intparams[IP_ALLOW_DYING])
	    ? JAIL_UPDATE | JAIL_DYING : JAIL_UPDATE);
	if (jid < 0) {
		jail_warnx(j, "%s", jail_errmsg);
		failed(j);
	}
	jailparam_free(setparams, 1);
	return jid;
}